import torch
import torch.nn as nn
import torch.nn.functional as F 

class DoubleConv(nn.Module):
"""conv=>BN=>ReLU=>conv=>BN=>ReLU """
	def __init__(self,in_channels, out_channels):
		super().__init__()
		self.doubleconv = nn.Sequential(
			nn.Conv2d(in_channels,out_channels,kernel_size=3,padding=1),
			nn.BatchNorm2d(out_channels),
			nn.ReLU(inplace=True),
			nn.Conv2d(in_channels,out_channels,kernel_size=3,padding=1),
			nn.BatchNorm2d(out_channels),
			nn.ReLU(inplace=True)
			)
	def forward(self,x):
		return self.doubleconv(x)

class Down(nn.Module):
"""Downsampling by max pooling """
	def __init__(self,in_channels,out_channels):
		super().__init__()
		self.down = nn.Sequential(
			nn.MaxPool2d(2),
			DoubleConv(in_channels,out_channels)
			)

	def forward(self,x):
		return self.down(x)

class Up(nn.Module):
	"""Upscaling then double conv"""
	def __init__(self,in_channels,out_channels,bilinear):
		super().__init__()
		if bilinear:
			self.up = nn.Upsample(scale_factor=2, mode='bilinear', align_corners=True)
				
		else:
			self.up = nn.ConvTranspose2d(in_channels // 2, in_channels // 2, kernel_size=2, stride=2)
		self.conv = DoubleConv(in_channels,out_channels)
				
	def forward(self,x1,x2):
		x1 = self.up(x1)
		diffY = x2.size()[2] - x1.size()[2]
		diffX = x2.size()[3] - x1.size()[3]
		x1 = F1.pad(x1,[diffX//2,diffX-diffX//2,diffY//2,diffY-diffY//2])
		x = torch.cat([x2,x1],dim=1)
		return self.conv(x)
		
class OutConv(nn.Module):
	def __init__(self,in_channels,out_channels):
		super().__init__()
		self.conv = nn.Conv2d(in_channels,out_channels, kernel_size=1)
	def forward(self,x):
		return self.conv(x)


class Unet(nn.Module):
	def __init__(self,n_channels,n_classes,bilinear = True):
		super(Unet,self).__init__()
		self.n_channels = n_channels
		self.n_classes = n_classes
		# This is for upsampling
		self.bilinear = bilinear

		self.inp = DoubleConv(n_channels,64)
		self.d1 = Down(64,128)
		self.d2 = Down(128,256)
		self.d3 = Down(256,512)
		self.d4 = Down(512,512)
		self.u4 = Up(512,512)
		self.u3 = Up(512,256)
		self.u2 = Up(256,128)
		self.u1 = Up(128,64)
		self.out = OutConv(64,n_channels)

	def forward(self,x):
		x1 = self.inp(x)
		x2 = self.d1(x1)
		x3 = self.d2(x2)
		x4 = self.d3(x3)
		x5 = self.d4(x4)
		x = self.u4(x5,x4)
		x = self.u3(x,x3)
		x = self.u2(x,x2)
		x = self.u1(x,x1)
		final = self.out(x)
		return final
		
if __name__ == '__main__':
	model = Unet(3,100)
	print(model)
   M S B A M L   `   `   `  ����M  I03_WPF控件模板, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null9!clr-namespace:_03_WPF控件模板_03_WPF控件模板  5   	   $    _03_WPF控件模板.MainWindow   5   	   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   3local!clr-namespace:_03_WPF控件模板     5   	     � Title$  
MainWindow��5   	   $	��450��6   $	��800��6)    � 	Resources 5	         FocusVisual �� Property �� Value �� StrokeDashArray J� SnapsToDevicePixels  Button.Static.Background �� Color  Button.Static.Border  Button.MouseOver.Background  Button.MouseOver.Border  Button.Pressed.Background  Button.Pressed.Border  Button.Disabled.Background  Button.Disabled.Border 	 Button.Disabled.Foreground 
 ButtonStyle1 �� 
TargetType �� 
TargetType	 ��Name
 ��Name �� Triggers P� Property P� Value �� 
TargetName��%X  &	        &	 �     &	 �     &	 �     &	     &	 6    &	 Y    &	 |    &	 �    &		 �    &	
 �    7   7  7  7  7  7  7  7  7  7 	 �� 5
   
   .�5      ��  � �� 5      �� 5      .R�5      �� $��2q�6$   $	 1 2R�6/   #��� ��6E    . $��1��6�   5      5      5      �� 5   
   $ 	#FFDDDDDD��6;   �� 5   
   $ 	#FF707070��67   �� 5   
   $ 	#FFBEE6FD��6>   �� 5   
   $ 	#FF3C7FB1��6:   �� 5   
   $ 	#FFC4E5F6��6<   �� 5   
   $ 	#FF2C628B��68   �� 5   
   $ 	#FFF4F4F4��6=   �� 5   
   $ 	#FFADB2B5��69   �� 5   
   $ 	#FF838383��6=   �� 5   
   " ��6%   .�5      ��  �@�FocusVisualStyle8   61   �� 5       � ��8  6+   �� 5       � ��8  6,   �� 5        � ��# � ��6+   �� 5!       � ��$ 1q�60   �� 5"       � ��$ Center=�6;   �� 5#       � ��$ Center=�69   �� 5$       � ��$ 1q�6(   �� 5%       � �� 5&      �� 5'      " ��6&   .R�5(      �� $	 border��6!   #��z��5)   !   #��z��5*   !   #��z��5+   !    . ._�5-      �� $
 contentPresenter��6/   |�.  #��z��5/   /   #��z��50   /   ��. # z 52   /   #��z��53   /   54       55      P� 56       �@��IsDefaulted . . �57   "   �� $ border��6@   # � ��6T    � ��58      P� 59       �@J�IsMouseOver . . �5:   "   �� $ border��6?   8   � ��6S   �� 5;   "   $ border��6@   8   � ��6T   5<      P� 5=       � �� . . �5>   "   �� $ border��6?   8   � ��6S   �� 5?   "   $ border��6@   8   � ��6T   5@      P� 5A       � {� .  . �5B   "   �� $ border��6?   8   � ��6S   �� 5C   "   $ border��6@   8   � ��6T   �� 5D   "   $ contentPresenter��6K   8 	  � ��6i   5E      5G      5I      5J      5K      .��5L      � .+�5M   
   ��  �� Orientation$ 
Horizontal=�6   .+�5P      �� #��� 
 6   $	��100��5Q      $��40��6!   ��5R      �� 5U      $ 
Horizontal=�6!   .+�5V      �� $��01��6!   �� 5W      $��02��6!   �� 5X      $��03��6!   5Y      5^      5_      5a      5b      
# Digital-image-processing Course                   #
## hdu Digital Image Processing Course's Classwork ##
#####################################################

#20200228<br>
022801:对每个像素求平均值。<br>
022802:显示图像。<br>
022803:图像二值化。<br>
022804:Mat的深复制和浅复制。<br>

#20200306<br>
030601:图像的RBG通道分离。<br>
030602:从摄像头中读取帧形成视频并显示。<br>
030603:图像上画圈，画线，画矩形。<br>
030604:统计图像通道1的直方图。<br>
030605:绘制图像通道1的直方图曲线。<br>

#20200313<br>
031301:用HSV模型实现简单磨皮美颜。<br>
031302:实现大津法和自适应阈值法二值化。<br>
031303:实现滑动可控制阈值二值化。<br>

#20200320<br>
032001:对coin.png先进行二值化，然后分别进行腐蚀、膨胀、开运算和闭运算。<br>
032002:对coin.png先进行二值化，然后进行连通域标记，并绘制出每个连通域的外接四边形（bounding box），并使用 cout <<，将硬币的个数输出至状态栏。<br>
032003:使用大津法分割IMG_1989.jpg，并对其进行连通域标记，利用图像形态学中所学的知识实现自动计算原点个数。<br>
032004:对clip.png进行自动计数。<br>

#20200327<br>
032701：读取摄像头图像，并对摄像头图像进行中值滤波。<br>
032702：读取摄像头图像，并对摄像头图像进行均值滤波。<br>
032703：读取摄像头图像，并对摄像头图像进行高斯均值滤波。<br>
032704：读取摄像头图像，并对摄像头图像进行边缘提取，分别提取x，y方向上的边缘，观察结果有何区别。<br>
032705：使用已经学过的算法，实现一个简单的磨皮程序，即人物皮肤的部分显得光滑。（mask，卷积，HSV范围限制）<br>

#20200403<br>
040301：canny算子。<br>
040302：旋转及缩放。<br>
040303：仿射变换。<br>
040304：投影变换。<br>
040305：图像矫正。<br>
040306：改进后的旋转。<br>

#20200410<br>
041001：通过OpenCV进行图像的旋转后，超出原尺寸的部分，会被自动裁剪，如何实现不自动裁剪的图像旋转。<br>
041002：HuoghLines函数实现霍夫变换。<br>
041003：HuoghLinesP函数实现霍夫变换。<br>

#20200417<br>
041701：提取和筛选图像轮廓。<br>
041702：提取和筛选图像轮廓。<br>
041703：提取和筛选图像轮廓。<br>

#20200424<br>
042401：手动实现hog。<br>

#20200508<br>
050801：鼠标响应画多边形。<br>
050802：傅里叶变换。<br>
050803：傅里叶逆变换。<br>
050804：傅里叶变换合成两张图片。<br>

#20200515<br>
051501：手动实现gamma矫正。<br>
051502：调用直方图均衡函数，进行直方图均衡处理，opencv原函数只能对单通道图像进行直方图均衡，要求实现可以对3通道图像进行直方图均衡。<br>
051503：图中有一些字，由于曝光不足无法观察到，请使用gamma矫正，并设置合适参数，找出隐藏的信息。<br>

#20200522<br>
052201：实现背景差分。<br>
052202：实现高斯建模及背景差分。<br>

#20200529<br>
052201：利用第九周缩写的基于HOG的图片相似度计算的函数，完成一个基于HOG的目标物体追踪程序。以下图中的右图为模板，实现在右图中的定位功能。<br>
052202：OpenCV模板匹配功能调用练习。<br>

#20200605<br>
060501：K means练习。<br>
060502：K means视频绿布处理。<br>

#20200612<br>
finalwork:数字图像处理大作业。<br>

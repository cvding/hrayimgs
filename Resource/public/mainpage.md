# 仿射变换库
> 在坐标系中定义了4种仿射变换，平移，缩放，旋转，错切，相关对应参数，请参看本文档

### 1. 4种变换如下图所示
![Affine](d:/WorkRoot/dddz/code/homegit/affine/Resource/public/Affine.png)
### 2. 变换公式如下图所示
![Formula](d:/WorkRoot/dddz/code/homegit/affine/Resource/public/Formule.png)<br />
**其中Q=Ry - Rx**

### 3. 需要注意的问题
- 明确仿射变换前后坐标系
- 明确输入点和输出点所处的坐标系

### 4. 一个简单的示例

```c
#include <stdio.h>
#include "Affine.h"
int32_t main()
{
	const float r = 3.1415926f / 4;
	/* 设置仿射系数 */
	skaffine coef = mvSetAffine(1, 1, r, 0, 1, 1);
	skamatrix trans;

	/* 将仿射系数转化为仿射矩阵 */
	mvAffine2Matrix(&coef, &trans);

	skpointf src, dst;

	src.x = 0;
	src.y = 0;

	/* 将输入点(0,0) 经过变换转化为(-1.414,0) */
	mvMapPoint(&src, &trans, &dst);

	printf("(%f,%f) ==> (%f,%f)\n", src.x, src.y, dst.x, dst.y);

	return 0;
}
```
附图示例:<br />
![Coordinate](d:/WorkRoot/dddz/code/homegit/affine/Resource/public/Coordinate.png)<br />
平面A中一点(0,0)在平面B中处于(-1.414,0)位置
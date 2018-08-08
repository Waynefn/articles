# 使用Beep()函数发出指定音高

C语言里自带了函数`Beep()`,

它的声明如下:

```
bool Beep(DWORD Freq,DWORD Duration);
```

该函数调用机箱喇叭(扬声器)发出指定音高长度的声音
`Freq`代表声音的频率,单位是赫兹
`Duration`代表声音的长度,单位是毫秒

如果我们想发出现在音乐的乐音,该如何做呢?



我们知道音高在音乐中的最小划分是半音,我们把一倍音程平均划分成12个半音,
因此每个音的频率数列是一个等比数列

公比

$$r=2^(1/12)=1.05946309411451$$

现代标准音A4的频率通常为440Hz,实际音乐会的时候也会定音为442Hz或者443Hz
知道了这些参数,我们可以写出求任意音名音高的函数,
首先定义一个枚举类型 `pitch`,
```
	enum pitch {
		C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B, X
	};
  
typedef pitch pitch_t;
```

这里面定义了12个半音的名称,其中s代表sharp,即升音#
其中`X`代表空音符,用于以后的扩展
求得音高的程序很简单,如下
首先定义两个常量,即之前提到的标准音高和公比
```
#define A4_PITCH 440
#define MUSIC_RATIO 1.05946309411451f
DWORD getFreqByName(pitch_t name, char num = 5)
	{
		if (name == X)return 0;
		int feq = pow(MUSIC_RATIO, ((int)name + 3)) * A4_PITCH;
		return pow(2, (num - 5))*feq;
	}
```
这个函数入口参数 name为枚举音名,num代表音的位置
例如中央C为C4, 钢琴最低音为A0

程序原理如下,为了计算方便,先求出C5的音高,由于C5比A4高3,因此使用当前的音名+3即可

同一音名都是2倍关系,再通过num求出具体音高

以下例子可以发出C5,D5,E5
```
	Beep(getFreqByName(C,5),1000);
	Beep(getFreqByName(D,5),1000);
	Beep(getFreqByName(E,5),1000);
```

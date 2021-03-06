# 对比Python和C++的正则表达式函数

C++标准库中提供正则表达式库 regex，由于之前使用Python的re比较多，导致对C++的库不够了解，犯了很多错误。这里写出来给大家作参考。
这里对比Python的特性进行说明。

## 1.  re.compile(pattern)   vs   std::regex(pattern)

这两个函数均用来生成正则匹配模式，Python的版本返回一个匹配模式对象，C++版本本身就是一个类，pattern是构造函数之一。

在正则表达式中为了方便，我们使用原生字符串。Python有r" ...." 这样的语法，例如下面的正则表达式识别三组连字符分开的数字，如 070-9458-12345
```python
import re
e=re.compile(r"(\d+)-(\d+)-(\d+)")
```
这样的好处是反斜杠不需要再被转义，既不需要写成 \\的形式
```python
e=re.compile("(\\d+)-(\\d+)-(\\d+)")
```
对应C++则是  R"(  ...   )"，注意它的边界是【引号+括号】  到 【括号+引号】，例如以下的表达
```C++
string a("(\\d+)-(\\d+)-(\\d+)");
string b{R"((\d+)-(\d+)-(\d+))"};
string c=R"""((\d+)-(\d+)-(\d+))"""
```
这里使用了三种初始化方法，也使用了三种字符串表示方法，第一种需要转义，第二种是刚才介绍的原生字符串，第三种则是增强版本的原生字符元，允许在引号和括号之间加入自定义的字符串作为分隔符，不然原生字符串仍然不能包含 ）“   这两个字符，例子中我们添加了两个引号，形成了类似Python的语法。

## 2. re.match(e1,target)    vs    std::regex_match(target, match,e2)

这两个函数均用来匹配正则表达式，其中target是目标字符串，e1是正则表达式，s2是std::regex对象，match是一个std::smatch对象。
Python版本返回一个match对象，如果不匹配则返回None。而C++版本返回bool值说明成功与否，并将结果保存到match对象内（该对象为引用传参）
```python
b=re.match("a","aaa")
b
#<_sre.SRE_Match object; span=(0, 1), match='a'>
```

```C++
using namespace std;
string a="aaa";
regex e("a");
smatch m;
auto r=regex_match(a,m,e);
//r: True
//m[0]:  "a"
```
## 3. re.subn(pattern,string,target)   vs    std::regex_replace(target,e2,string)

这两个函数用来替换字符串，比如我们将 1234_6789 替换成  6789_1234
```python
re.subn(r"(\d{4})_(\d{4}))",r"\2_\1","1234_6789")
```
Python使用\1 、\2  之类的数字来引用分组（无分组上限，但要考虑堆栈情况），对应C++代码为
```python
string a("1234_6789");
regex e(R"((\d{4})_(\d{4}))");
auto r=std::regex_replace(a,e,"$2_$1");
```
C++ 使用 $1 ~ $ 99 来引用分组，最大为99组 （而不是一般的9组）

以上的普通使用都没什么问题，但是分组引用在特殊情况下均会出问题，比如想把1234_6789 替换成  6789_1234  ，并且将下划线换成5，也就是最终结果 678951234
若直接使用
```python
re.subn(r"(\d{4})_(\d{4}))",r"\25\1","1234_6789")
```
会被当成引用第25分组而出错
同样在C++里
```C++
string a("1234_6789");
regex e(R"((\d{4})_(\d{4}))");
auto r=std::regex_replace(a,e,"$25$1");
```
也会当成引用25分组而没有结果。如何解决该问题呢？

Python和C++使用不同的方法，Python中有一个特殊转义 `\g<groupnum> ` 可以指定分组号码
所以可以进行如下解决
```python
re.subn(r"(\d{4})_(\d{4}))",r"\g<2>5\1","1234_6789")
```
而在C++中由于最大组是99，所以可以用两位数指定分组（这在Python中行不通）
```C++
string a("1234_6789");
regex e(R"((\d{4})_(\d{4}))");
auto r=std::regex_replace(a,e,"$025$1");
```
使用上述两种方法最终都能得到正确结果678951234。

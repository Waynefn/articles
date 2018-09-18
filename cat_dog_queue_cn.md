# 猫狗队列（C++解法）

## 题目

原题目使用Java作为示范，本文章提供C++解法。
猫狗两个类的定义如下
```C++

public class Pet {  
    private String type;  
    public Pet(String type){  
        this.type = type;  
    }  
    public String getPetType(){  
        return this.type;  
    }  
}

public class Dog extends Pet {  
  
    public Dog() {  
        super("dog");  
    }  
  
}

public class Cat extends Pet {  
  
    public Cat(String type) {  
        super("cat");  
  
    }  
  
}
```
实现一种猫狗队列的结构，要求如下：

+ 用户可以调用add方法将cat类或者dog类的实例放入队列中
+ 用户可以调用pollAll方法，将队列中所有的实例按照队列的先后顺序依次弹出
+ 用户可以调用pollDog方法，将队列中dog类的实例按照队列的先后顺序依次弹出
+ 用户可以调用pollCat方法，将队列中cat类的实例按照队列的先后顺序依次弹出
+ 用户可以调用isEmpty方法，检查队列中是否还有dog和cat的实例
+ 用户可以调用isDogEmpty方法，检查队列中是否还有do的实例
+ 用户可以调用isCatEmpty方法，检查队列中是否还有cat的实例

附上原题目的C++代码
```C++
class Pet {
	string type;
public:
	Pet(string type) {
		this->type = type;
	}
	string getPetType() {
		return this->type;
	}
};
 
 
class Dog :public Pet {
public:
	Dog():Pet("Dog") {}
};
 
class Cat :public Pet {
public:
	Cat() : Pet("Cat") {}
};

```




## 我的分析

这道题考察队列的基本操作，要求构造一种队列同时记录两种数据类型。但在本列中猫狗类拥有共同基类Pet。

基本方法是写一个带有时间戳的类型PetCount，使其含有一个用于记录先后顺序的计数器count，每次入队的时候根据类型进入对应的队列，并赋予独一无二的时间戳。出队的时候根据要求比较先后时间即可。

现定义PetCount类如下：
```C++
class PetCount {
	Pet* pet;
	int count;
public:
	PetCount(Pet* pet, int cnt){
		this->pet = pet;
		this->count = cnt;
	}
	Pet* getPet() {
		return pet;
	}
	int getCount() {
		return this->count;
	}
	string getPetType() {
		return pet->getPetType();
	}
};
```
这里使用指针的原因是，C++中父类即使用来保存子类，也不能再次转换成子类，因为数据会被截断。只有使用指针才能实现类的转换。另一种更方便的方式是定义两种Count类，分别存储猫狗两种类。
之后题目所需类的实现如下所示：
```C++
class DogCatQueue {
	queue<PetCount>catq;
	queue<PetCount>dogq;
	int count;
public:
	DogCatQueue():count(0) {}
	void add(Dog &d) {
		dogq.push(PetCount(&d,count++));
	}
	void add(Cat &c) {
		catq.push(PetCount(&c, count++));
	}
	bool empty(){
		return dogq.empty() && catq.empty();
	}
	bool DogEmpty() { return dogq.empty(); }
	bool CatEmpty() { return catq.empty(); }
 
	Cat *pollCat(){
		Cat* r= static_cast<Cat*>(catq.front().getPet());
		catq.pop();
		return r;
	}
	Dog *pollDog() {
		Dog*r= static_cast<Dog*>(dogq.front().getPet());
		dogq.pop();
		return r;
	}
	Pet* pollAll() {
		if (empty())return nullptr;
		else if (DogEmpty())return pollCat();
		else if (CatEmpty())return pollDog();
		return (dogq.front().getCount() > catq.front().getCount()) ? (Pet*)pollDog(): (Pet*)pollCat();
	}
 
 
};
```
这里有一个问题需要考虑，java版本不涉及指针，都是引用在传递。而C++里的指针会引发内存管理的问题。在本题中，所有内存均由交付之前的代码负责释放，队列只负责保存一个引用地址。

另外需要注意本代码使用了stl的queue模板。由于安全性和异常处理的考虑，stl模板的pop()均不返回值。

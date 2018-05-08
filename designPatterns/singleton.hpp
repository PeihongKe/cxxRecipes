

class Singleton
{
private:
	static Singleton& getSingleton()
	{
		static Singleton single;
		return single;

	}
public:
	Singleton() {};
	Singleton(const Singleton&);
	//an implicitly generated copy assignment operator will return a non-const reference
	Singleton& operator= (const Singleton&) {};
	~Singleton() {};
};
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

//***************usage******************
//class SClass : public Singleton<SClass>
//{
//public:
//    friend class Singleton<SClass>;
//
//protected:
//    SClass();
//    virtual ~SClass();
//}
//SClass &s = SClass::instance();
//**************************************

template <class T>
class Singleton
{
public:
    static T &instance()
    {
        static T t;
        use( i );
        return t;
    }

protected:
    Singleton() {}
    virtual ~Singleton() {}

private:
    Singleton( const Singleton& );
    Singleton& operator = ( const Singleton& );
    static T & i;
    static void use( T const & ) {}
};

template<class T>
T & Singleton< T >::i = Singleton< T >::instance();

#endif //SINGLETON_HPP
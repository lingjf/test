
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dbghelp.h>  /* SymFromAddr */

#pragma comment(lib, "Dbghelp.lib")

   HANDLE hProcess;
void *frames[100];

void get1(void* addr)
{
 char buffer[sizeof(SYMBOL_INFO) + 256];
   SYMBOL_INFO* symbol = (SYMBOL_INFO*)buffer;
   symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
   symbol->MaxNameLen = 256;
   if (!SymFromAddr(hProcess, (DWORD64)(addr), 0, symbol))
      return ;
   void* offset=NULL;
   if (memcmp("ILT+", symbol->Name, 4) == 0) {  // ILT (Incremental Link Table), JMP(e9)
      offset = (void*)((unsigned char*)symbol->Address + 5 + *(long*)((unsigned char*)symbol->Address + 1));
      
   }
   
  ::printf("%s %p %lld %p %x\n",symbol->Name, symbol->Address, (long long)addr-(long long)symbol->Address, offset, *(unsigned char*)symbol->Address);
    if (*(unsigned char*)symbol->Address==0xe9)
       get1(offset);
}

template <typename Class, typename Signature>
struct h2_mfp;
template <typename Class, typename ReturnType, typename... Args>
struct h2_mfp<Class, ReturnType(Args...)> {

   static void* A(ReturnType (*f)(Args...))
   {
      return (void*)f;
   }

   union U {
      ReturnType (Class::*f)(Args...);
      void* p;
      long long v;
   };

 
   static void* A(ReturnType (Class::*f)(Args...))
   {
      U u{f};
      return u.p;
   }
 
};

class A
{
public:
  long long a;
  A() {}
  const char* f0() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fa0"; }
  virtual const char* f1() = 0;
  virtual const char* f2() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fa2"; }
};


class B: public A
{
public:
  long long b;
  B() {}
  const char* f0() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fb0"; }
  virtual const char* f1() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fb1"; }
  virtual const char* f2() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fb2"; }
};

class C: public A
{
public:
  long long c;
  C() {}
  const char* f0() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fc0"; }
  virtual const char* f1() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fc1"; }
  virtual const char* f2() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fc2"; }
};

class D: public B, public C
{
public:
  long long d;
  D() {}
  const char* f0() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fd0"; }
  virtual const char* f1() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fd1"; }
  virtual const char* f2() { CaptureStackBackTrace(0, sizeof(frames) / sizeof(frames[0]), frames, NULL); get1(frames[0]); return "fd2"; }
};


class Shape {
 public:
   int x, y;

   Shape() : x(0), y(0) {}

 private:
   static int fly(int x, int y) { return 0; }
   static int fly(int xy) { return 1; }

   int go(int x, int y) { return 1; }
   int go(int xy) { return 2; }

   virtual int work(int x, int y) { return 3; }
   virtual int work(int xy) { return 4; }
};

class Rect : public Shape {
 public:
   Rect(int _x, double _y) {}
   virtual int work(int x, int y) { return 4; }
};

class Circle : public Shape {
 public:
   Circle(char* _x) {}
   virtual int work(int x, int y) { return 5; }
};

class Color {
 public:
   int r, g, b;
   virtual ~Color() {}
   virtual int print(int x, int y) { return 10; }
};

// class Six : public Rect, public Color {
//  public:
//    Six(int _1, int _2, int _3, int _4, int _5, int _6) : Rect(0, 0) {}
//    virtual int work(int x, int y) { return 6; }
//    virtual int print(int x, int y) { return 20; }
// };

class Six  : public Shape, public Color {
 public:
   Six(int _1, int _2, int _3, int _4, int _5, int _6)    {}
   virtual int work(int x, int y) { return 6; }
   virtual int print(int x, int y) { return 20; }
};


int
main(int argc, char* argv[])
{
   hProcess = GetCurrentProcess();
   SymInitialize(hProcess, NULL, TRUE);
  
//   A a;
  B b;
  C c;
  D d;
   
      Six six(1, 2, 3, 4, 5, 6);
   
     void* p4 =  h2_mfp<Six, int(int, int)>::A(&Six::work);
      get1(p4);
//       typedef int (*Six_Work)(Six*, int, int);
//       OK(6, ((Six_Work)p4)(&six, 1, 1));
::printf("%d\n", six.work(1,1));
      void* p5 = h2_mfp<Six, int(int, int)>::A(&Six::print);
//       OK(NotNull, p5);
//       typedef int (*Six_Print)(Six*, int, int);
//       OK(20, ((Six_Print)p5)(&six, 1, 1));
   get1(p5);
   ::printf("%d\n", six.print(1,1));
   

  b.f0();b.f1();b.f2(); // h2_mfp<B,const char*()>(&B::f1)
  get1(h2_mfp<B,const char*()>::A(&B::f0) ); get1(h2_mfp<B,const char*()>::A(&B::f1) ); get1(h2_mfp<B,const char*()>::A(&B::f2));
  c.f0();c.f1();c.f2();
  d.f0();d.f1();d.f2();
   get1(h2_mfp<D,const char*()>::A(&D::f0) ); get1(h2_mfp<D,const char*()>::A(&D::f1) ); get1(h2_mfp<D,const char*()>::A(&D::f2));
   
   
//   printf("%s\n", a.f1());
//   printf("&A=%p, &A.a=%p", &a, &a.a);
//   printf(", &A.f0=%p", &A::f0);
//   printf(", &A.f1=%p", &A::f1);
//   printf(", &A.f2=%p\n", &A::f2);

//   printf("%s\n", b.f1());
  printf("&B=%p, &B.b=%p", &b, &b.b);
  printf(", &B.f0=%p", &B::f0);
  printf(", &B.f1=%p", &B::f1);
  printf(", &B.f2=%p\n", &B::f2);

//   printf("%s\n", c.f1());
  printf("&C=%p, &C.c=%p", &c, &c.c);
  printf(", &C.f0=%p", &C::f0);
  printf(", &C.f1=%p", &C::f1);
  printf(", &C.f2=%p\n", &C::f2);

//   printf("%s\n", d.f1());
  printf("&D=%p, &D.d=%p", &d, &d.d);
  printf(", &D.f0=%p", &D::f0);
  printf(", &D.f1=%p", &D::f1);
  printf(", &D.f2=%p\n", &D::f2);

 
    
//       typedef const char* (*F1)(B*);
// typedef  const char *(__cdecl B::* F2)(void);
//   union {
//     void * a;
//     F2 c;
//     F1 b;
//   }u;
//     u.c=    &B::f1 ;
  
//      u.a=   reinterpret_cast<void*>(&A::f1) ;
    
// printf("%p %s\n", &(b.f1), (u.b)(&b));
//   u.c=    &B::f2 ;
//   printf("%s\n", (u.b)(&b));
  return 0;
}

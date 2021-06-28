
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class A
{
public:
  long long a;
  A() {}
  const char* f0() { return "fa0"; }
  virtual const char* f1() { return "fa1"; }
  virtual const char* f2() { return "fa2"; }
};

class B: public A
{
public:
  long long b;
  B() {}
  const char* f0() { return "fb0"; }
  virtual const char* f1() { return "fb1"; }
  virtual const char* f2() { return "fb2"; }
};

class C: public A
{
public:
  long long c;
  C() {}
  const char* f0() { return "fc0"; }
  virtual const char* f1() { return "fc1"; }
  virtual const char* f2() { return "fc2"; }
};

class D: public B, public C
{
public:
  long long d;
  D() {}
  const char* f0() { return "fd0"; }
  virtual const char* f1() { return "fd1"; }
  virtual const char* f2() { return "fd2"; }
};

int
main(int argc, char* argv[])
{
  A a;
  B b;
  C c;
  D d;
//   printf("%s\n", a.f1());
  printf("&A=%p, &A.a=%p", &a, &a.a);
  printf(", &A.f0=%p", &A::f0);
  printf(", &A.f1=%p", &A::f1);
  printf(", &A.f2=%p\n", &A::f2);

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

 
    
      typedef const char* (*F1)(A*);
typedef  const char *(__cdecl A::* F2)(void);
  union {
    void * a;
    F2 c;
    F1 b;
  }u;
    u.c=    &A::f1 ;
  
     u.a=   reinterpret_cast<void*>(&A::f1) ;
    
printf("%s\n", u.b(nullptr));
  return 0;
}


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
  printf(", &A.f1=%d", &A::f1);
  printf(", &A.f2=%d\n", &A::f2);

//   printf("%s\n", b.f1());
  printf("&B=%p, &B.b=%p", &b, &b.b);
  printf(", &B.f0=%p", &B::f0);
  printf(", &B.f1=%d", &B::f1);
  printf(", &B.f2=%d\n", &B::f2);

//   printf("%s\n", c.f1());
  printf("&C=%p, &C.c=%p", &c, &c.c);
  printf(", &C.f0=%p", &C::f0);
  printf(", &C.f1=%d", &C::f1);
  printf(", &C.f2=%d\n", &C::f2);

//   printf("%s\n", d.f1());
  printf("&D=%p, &D.d=%p", &d, &d.d);
  printf(", &D.f0=%p", &D::f0);
  printf(", &D.f1=%d", &D::f1);
  printf(", &D.f2=%d\n", &D::f2);
  return 0;
}

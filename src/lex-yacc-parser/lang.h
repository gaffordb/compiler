#pragma once
#include <memory>
#include <iostream>

using namespace std;

enum TData { ival, bval, strval, funval, fixval };

union LData {
  int i;
  bool b;
  const char* str;
  struct EFun* fun;
  struct EFix* fix;
};

struct LitData {
  TData type;
  LData data;
};

struct Exp {
  virtual LitData eval() = 0;//{fprintf(stderr, "can't eval raw exp\n");exit(1);}
  //std::ostream& operator<<(std::ostream& strm);
  virtual shared_ptr<string> display(void) = 0;// {fprintf(stderr, "can't display raw exp\n");exit(1);}
  virtual void subst(LitData val, const char* var) = 0;
};

struct ELit : public Exp {
  LitData value;
  ELit(int _value);
  ELit(bool _value);
  ELit(LitData& ld);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct EPlus : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EPlus(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct EMinus : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EMinus(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct EDiv : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EDiv(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct EMult : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EMult(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct ELeq : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  ELeq(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct EBigger : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EBigger(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct EIf : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  shared_ptr<Exp> e3;
  EIf(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Exp> _e3);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct EVar : public Exp {
  const char* var;
  shared_ptr<Exp> e1;
  EVar(const char* var);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct ELet : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  shared_ptr<Exp> e3;
  ELet(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Exp> _e3);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct EFun : public Exp {
  shared_ptr<Exp> e1; //should be EVar
  shared_ptr<Exp> e2;
  shared_ptr<Exp> apply(LitData val, const char* var);
  EFun(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};
/*
struct EFix2 : public EFun {
  shared_ptr<Exp> e3;
  EFix(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Exp> _e3);
  LitData eval();
  shared_ptr<Exp> apply(LitData val, const char* var);
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};
*/
struct EFix : public Exp {
  const char* fun_name;
  shared_ptr<Exp> e1; //should be EVar
  shared_ptr<Exp> e2; //body
  shared_ptr<Exp> apply(LitData val, const char* var);
  EFix(const char* _fun_name, shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

struct EApp : public Exp {
  shared_ptr<Exp> e1; //should be EFun
  shared_ptr<Exp> e2;
  EApp(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
};

//tostring junk
std::ostream& operator<<(std::ostream& strm, LitData const& ld);
std::ostream& operator<<(std::ostream& strm, shared_ptr<Exp> exp);

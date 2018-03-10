#pragma once
#include <memory>
#include <iostream>

using namespace std;

enum TData { ival, bval, strval, funval };

union LData {
  int i;
  bool b;
  const char* str;
  struct EFun* fun;
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
  EFun(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
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
/*
std::ostream& operator<<(std::ostream& strm, ELit const& ld);
std::ostream& operator<<(std::ostream& strm, EPlus const& ld);
std::ostream& operator<<(std::ostream& strm, EMinus const& ld);
std::ostream& operator<<(std::ostream& strm, EDiv const& ld);
std::ostream& operator<<(std::ostream& strm, EMult const& ld);
std::ostream& operator<<(std::ostream& strm, ELeq const& ld);
std::ostream& operator<<(std::ostream& strm, EIf const& ld);
*/

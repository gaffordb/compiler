#pragma once
#include <memory>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*************************Data**************************************/

enum TData {
  ival, bval,
  strval, funval,
  fixval, pairval,
  unitval, ptrval,
  listval
};

union LData {
  int i;
  bool b;
  const char* str;
  struct EFun* fun;
  struct EFix* fix;
  struct EPair* pair;
  struct EPtr* ptr;
  struct EList* lst;
};

struct LitData {
  TData type;
  LData data;
};

/*************************TYPES**************************************/
struct Typ {
  virtual string display() = 0;
};

struct TInt : public Typ {
  TInt();
  string display();
};

struct TBool : public Typ {
  TBool();
  string display();
};

struct TUnit : public Typ {
  TUnit();
  string display();
};

struct TPair : public Typ {
  shared_ptr<Typ> t1;
  shared_ptr<Typ> t2;
  TPair(shared_ptr<Typ> _t1, shared_ptr<Typ> _t2);
  string display();
};

struct TFun : public Typ {
  shared_ptr<Typ> tin;
  shared_ptr<Typ> tout;
  TFun(shared_ptr<Typ> _tin, shared_ptr<Typ> _tout);
  string display();
};

struct TRef : public Typ {
  shared_ptr<Typ> t;
  TRef(shared_ptr<Typ> _t);
  string display();
};

struct TArray : public Typ {
  shared_ptr<Typ> t;
  TArray(shared_ptr<Typ> _t);
  string display();
};

struct TArrGet : public Typ {
  shared_ptr<Typ> t;
  TArrGet(shared_ptr<Typ> _t);
  string display();
};

struct TList : public Typ {
  shared_ptr<Typ> t;
  TList(shared_ptr<Typ> _t);
  string display();
};

/*************************Expressions**************************************/

struct Exp {
  virtual LitData eval() = 0;
  virtual shared_ptr<string> display(void) = 0;
  virtual void subst(LitData val, const char* var) = 0;
  unordered_map<string, shared_ptr<Typ> > ctx; //mapping of vars to type
  virtual shared_ptr<Typ> typecheck() = 0;
};

struct ELit : public Exp {
  LitData value;
  ELit(int _value);
  ELit(bool _value);
  ELit(LitData& ld);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EPlus : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EPlus(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EMinus : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EMinus(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EDiv : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EDiv(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EMult : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EMult(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct ELeq : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  ELeq(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EGeq : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EGeq(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EBigger : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EBigger(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct ESmaller : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  ESmaller(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EIf : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  shared_ptr<Exp> e3;
  EIf(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Exp> _e3);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EVar : public Exp {
  const char* var;
  shared_ptr<Exp> e1;
  EVar(const char* var);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct ELet : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  shared_ptr<Exp> e3;
  shared_ptr<Typ> tv;
  ELet(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Exp> _e3, shared_ptr<Typ> _tv);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EFun : public Exp {
  shared_ptr<Exp> e1; //should be EVar
  shared_ptr<Exp> e2;
  shared_ptr<Typ> tin;
  shared_ptr<Typ> tout;
  shared_ptr<Exp> apply(LitData val, const char* var);
  EFun(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Typ> _t1, shared_ptr<Typ> _t2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EFix : public Exp {
  const char* fun_name;
  shared_ptr<Exp> e1; //should be EVar
  shared_ptr<Exp> e2; //body
  shared_ptr<Typ> tin;
  shared_ptr<Typ> tout;
  shared_ptr<Exp> apply(LitData val, const char* var);
  EFix(const char* _fun_name, shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Typ> _t1, shared_ptr<Typ> _t2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EApp : public Exp {
  shared_ptr<Exp> e1; //should be EFun
  shared_ptr<Exp> e2;
  EApp(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EPair : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EPair(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EFst : public Exp {
  shared_ptr<Exp> e;
  EFst(shared_ptr<Exp> _e);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct ESnd : public Exp {
  shared_ptr<Exp> e;
  ESnd(shared_ptr<Exp> _e);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EUnit : public Exp {
  EUnit();
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct ERef : public Exp {
  shared_ptr<Exp> e;
  ERef(shared_ptr<Exp> _e);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EDeref : public Exp {
  shared_ptr<Exp> e;
  EDeref(shared_ptr<Exp> _e);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct ESet : public Exp {
  shared_ptr<Exp> e1, e2;
  ESet(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct ESeq : public Exp {
  shared_ptr<Exp> e1, e2;
  ESeq(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EPtr : public Exp {
  unsigned int addr;
  shared_ptr<Typ> t;
  shared_ptr<EPtr> self;
  EPtr(unsigned int addr, shared_ptr<Typ> _t);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EWhile : public Exp {
  shared_ptr<Exp> guard, body;
  EWhile(shared_ptr<Exp> _guard, shared_ptr<Exp> _body);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EArrRef : public Exp {
  shared_ptr<Exp> e;
  shared_ptr<Typ> t;
  EArrRef(shared_ptr<Exp> _e, shared_ptr<Typ> _t);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EArrGet : public Exp {
  shared_ptr<Exp> arr;
  shared_ptr<Exp> index;
  bool is_get;
  EArrGet(shared_ptr<Exp> _arr, shared_ptr<Exp> _index);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EArrSet : public Exp {
  shared_ptr<Exp> arr;
  shared_ptr<Exp> index;
  EArrSet(shared_ptr<Exp> _arr, shared_ptr<Exp> _index);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EList : public Exp {
  shared_ptr<Typ> t;
  shared_ptr<Exp> e; //next
  shared_ptr<LitData> data; //payload
  shared_ptr<Exp> self; //bullshit
  EList(shared_ptr<Typ> _t);
  EList(shared_ptr<Exp> _e, shared_ptr<Typ> _t);
  EList(shared_ptr<Exp> _e, shared_ptr<LitData> _data);
  LitData eval();
  shared_ptr<string> display(void);
  string display_inner(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct ECons : public Exp {
  shared_ptr<Exp> e1, e2;
  ECons(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct ECar : public Exp {
  shared_ptr<Exp> e;
  ECar(shared_ptr<Exp> _e);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct ECdr : public Exp {
  shared_ptr<Exp> e;
  ECdr(shared_ptr<Exp> _e);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

struct EEmpty : public Exp {
  shared_ptr<Exp> e;
  EEmpty(shared_ptr<Exp> _e);
  LitData eval();
  shared_ptr<string> display(void);
  void subst(LitData val, const char* var);
  shared_ptr<Typ> typecheck();
};

/*************************STACK**************************************/

extern unordered_map<unsigned int, shared_ptr<LitData> > g_stack;
extern unsigned int g_stack_next_alloc;

void set_ptr(unsigned int addr, shared_ptr<LitData> val);
unsigned int ptr_alloc();
shared_ptr<LitData> get_ptr(unsigned int addr);

/*************************MISC**************************************/

LitData make_data(shared_ptr<Exp> e);

//tostring junk
std::ostream& operator<<(std::ostream& strm, LitData const& ld);
std::ostream& operator<<(std::ostream& strm, shared_ptr<Exp> exp);

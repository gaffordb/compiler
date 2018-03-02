#pragma once
#include <memory>
#include <iostream>

using namespace std;

enum TData { ival, bval };

union LData {
  int i;
  bool b;
};

struct LitData {
  TData type;
  LData data;
};

std::ostream& operator<<(std::ostream& strm, LitData const& ld);

struct Exp {
  virtual LitData eval() = 0;
};

struct ELit : public Exp {
  LitData value;
  ELit(int _value);
  ELit(bool _value);
  LitData eval();
};

/*
struct EBLit : public ELit {
bool value;
EBLit(bool _value);
LitData eval();
};
*/

struct EPlus : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EPlus(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
};

struct EMinus : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EMinus(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
};

struct EDiv : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EDiv(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
};

struct EMult : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  EMult(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
};

struct ELeq : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  ELeq(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2);
  LitData eval();
};

struct EIf : public Exp {
  shared_ptr<Exp> e1;
  shared_ptr<Exp> e2;
  shared_ptr<Exp> e3;
  EIf(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Exp> _e3);
  LitData eval();
};

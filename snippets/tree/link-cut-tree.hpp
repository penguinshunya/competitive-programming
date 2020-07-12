#include "../template.hpp"

struct LinkCutTree {
  struct Node {
    Node *l, *r, *p;
    int k;
    Node(int k) : k(k), l(nullptr), r(nullptr), p(nullptr) {}
    bool is_root() {
      return !p || (p->l != this && p->r != this);
    }
  };
  int n;
  vector<Node *> nodes;
  LinkCutTree(int n) : n(n), nodes(n) {
    for (int i = 0; i < n; i++) {
      nodes[i] = new Node(i);
    }
  }
  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if ((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }
  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if ((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }
  void splay(Node *t) {
    while (!t->is_root()) {
      auto *p = t->p;
      if (p->is_root()) {
        if (p->l == t) rotr(t);
        else rotl(t);
        continue;
      }
      auto *q = p->p;
      if (q->l == p) {
        if (p->l == t) rotr(p), rotr(t);
        else rotl(t), rotr(t);
      } else {
        if (p->r == t) rotl(p), rotl(t);
        else rotr(t), rotl(t);
      }
    }
  }
  int expose(int k) {
    Node *t = nodes[k];
    Node *rp = nullptr;
    for (auto *cur = t; cur; cur = cur->p) {
      splay(cur);
      cur->r = rp;
      rp = cur;
    }
    splay(t);
    return rp->k;
  }
  void link(int v, int u) {
    expose(v);
    expose(u);
    nodes[v]->p = nodes[u];
    nodes[u]->r = nodes[v];
  }
  int lca(int v, int u) {
    expose(v);
    return expose(u);
  }
};
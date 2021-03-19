#include "../BST/BST.h"
template <typename T> class Splay : public BST<T> {
    protected: 
        BinNodePosi(T) splay(BinNodePosi(T) v);
    public:
        BinNodePosi(T) & search(const T & c);
        BinNodePosi(T) insert(const T & e);
        bool remove(const T & e); 
}

template <typename T> BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v) {
    if (!v) return NULL;
    BinNodePost(T) p; BinNodePosi(T) g;
    while ((p = v->parent) && (g = p->parent)) {
        BinNodePost(T) gg = g->parent;
        if (IsLChild(*v)) {
            if (IsLChild(*p)) {
                /*zig-zig*/
                attachAsLChild(g, p->rc);
                attachAsLChild(p, v->rc);
                attachAsRChild(p, g);
                attachAsRChild(v, p);
            } else {
                /*zig-zag*/
                attachAsRChild(g, v->rc);
                attachAsLChild(p, v->lc);
                attachAsLChild(v, g);
                attachAsRChild(v, p);
            }
        } else if (IsRChild(*p)) {
            /*zag-zag*/
            attachAsRChild(g, p->lc);
            attachAsRChild(p, v->lc);
            attachAsLChild(p, g);
            attachAsLChild(v, p);
            
        } else {
            /*zag-zig*/
            attachAsLChild(g, p->rc);
            attachAsLChild(p, v->rc);
            attachAsRChild(p, g);
            attachAsRChild(v, p);
        
        }

        if (!gg) v->parent = NULL; // v is root
        else (g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
        updateHeight(g); updateHeight(p); updateHeight(v);    
    }
    // finished double extend, g must be null but not p
    if (p = v->parent) {
        // p is root, screw again
        if (IsLChild(*v)) { 
            attachAsLChild(p, v->rc);
            attachAsRChild(v, p);
        } else {
            attachAsRChild(p, v->lc);
            attachAsLChild(v, p);
        }
        udpateHeight(p);
        updateHeight(v);

    }
    v->parent = NULL;   
    return v;    

}


template <typename T> BinNodePosi(T) & Splay<T>::search(const T & e) {
    BInNodePosi(T) p = searchIn(_root, e, _hot=NULL);
    _root = splay(p ? p : _hot);
    // _hot must be pushed to root
    return _root;
}

template <typename T> BinNodePosi(T) & Splay<T>::insert(const T & e) {
    if (!root) {
        _size ++;
        return _root = new BinNodePosi<T> (e);
    }
    if (e == search(e)->data) return _root;
    _size ++;
    BinNodePosi(T) t = _root;
    if (_root->data < e) {
        // insert node, and t, t->rc are children
        t->parent = _root = new BinNodePosi<T> (e, NULL, t, t->rc);
        if (HasRChild(*t)) {
            t->rc->parent = _root;
            t->rc = NULL;
        }
    } else {
        t->parent = _root = new BinNodePosi<T> (e, NULL, t->lc, t);
        if (HasLChild(*t)) {
            t->lc->parent = _root;
            t->lc = NULL;
        }
    }

    updateHeightAbove(t);
    return _root;
}

template<typename T> bool Splay<T>::remove(const T & e) {
    if (!_root || (e != search(e)->data)) return false;
    BinNodePosi(T) w = _root;
    if (!HasLChild(*_root)) {
        _root = _root->rc;
        if (_root) _root->parent = NULL;
    } else if (!HasRChild(*_root)) {
        _root = _root->lc;
        if (_root) _root->parent = NULL;
    } else {
        BInNodePosi(T) lTree = _root->lc;
        lTree->parent = NUll;
        _root->lc = NULL;
        _root = _root->rc;
        _root->parent = NULL;
        // this search must failed, but we can get the smallest node of rc
        search(w->data);
        // assert: we got the smallest node and its lc should be NULL
        _root->lc = lTree;
        lTree->parent = _root;
    }
    release(w->data);
    release(w);
    _size --;
    if (_root) updateHeight(_root);
    return true;
}

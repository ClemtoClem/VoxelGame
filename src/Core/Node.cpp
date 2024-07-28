#include "Node.hpp"
#include <iostream>
#include "Logger.hpp"

// Constructor
Node::Node(const std::string &name) 
    : _name(name), 
      _parent(nullptr), 
      _firstChild(nullptr), 
      _lastChild(nullptr), 
      _childCount(0), 
      _previous(nullptr), 
      _next(nullptr) {}

// Destructor
Node::~Node() {
    removeAllChildren();
}

/* Setters */

void Node::setName(const std::string &name) {
    _name = name;
}

void Node::setParent(std::shared_ptr<Node> parent) {
    _parent = parent;
}

void Node::setPrevious(std::shared_ptr<Node> previous) {
    _previous = previous;
}

void Node::setNext(std::shared_ptr<Node> next) {
    _next = next;
}

/* Getters */

const std::string &Node::getName() const {
    return _name;
}

std::shared_ptr<Node> Node::getParent() const {
    return _parent;
}

std::shared_ptr<Node> Node::getFirstChild() const {
    return _firstChild;
}

std::shared_ptr<Node> Node::getLastChild() const {
    return _lastChild;
}

std::shared_ptr<Node> Node::getPrevious() const {
    return _previous;
}

std::shared_ptr<Node> Node::getNext() const {
    return _next;
}

/* Methods to manage children */

bool Node::addChild(std::shared_ptr<Node> child) {
    if (!child) return false;
    if (getChild(child->getName())) {
        LOG(Warning) << "Child '" << child->getName() << "' already exists";
        return false;
    }
    
    child->setParent(shared_from_this());

    if (!_firstChild) {
        _firstChild = child;
        _lastChild = child;
    } else {
        _lastChild->setNext(child);
        child->setPrevious(_lastChild);
        _lastChild = child;
    }
    ++_childCount;
    return true;
}

void Node::removeChild(std::shared_ptr<Node> child) {
    if (!child && _childCount > 0) return;

    if (child->getParent() != shared_from_this()) return;

    if (child == _firstChild) {
        _firstChild = child->getNext();
    }

    if (child == _lastChild) {
        _lastChild = child->getPrevious();
    }

    if (child->getPrevious()) {
        child->getPrevious()->setNext(child->getNext());
    }

    if (child->getNext()) {
        child->getNext()->setPrevious(child->getPrevious());
    }

    child->setParent(nullptr);
    child->setPrevious(nullptr);
    child->setNext(nullptr);
    --_childCount;
}

void Node::removeAllChildren() {
    while (_firstChild) {
        removeChild(_firstChild);
    }
}

size_t Node::getChildCount() const {
    return _childCount;
}

std::shared_ptr<Node> Node::detachChild(const std::string &name) {
    if (_childCount == 0 || name.empty()) return nullptr;

    auto child = getChild(name);
    if (!child) return nullptr;

    removeChild(child);

    return child;
}

// Method to get child by name
std::shared_ptr<Node> Node::getChild(const std::string &name) {
    if (_childCount == 0 || name.empty()) return nullptr;

    auto child = _firstChild;
    while (child) {
        if (child->getName() == name) {
            return child;
        }
        child = child->getNext();
    }
    return nullptr;
}

// Method to find child by path
std::shared_ptr<Node> Node::findChild(const std::string &path) {
    if (_childCount == 0 || path.empty()) return nullptr;

    size_t pos = path.find('/');
    std::string current = path.substr(0, pos);
    std::string remaining = pos == std::string::npos ? "" : path.substr(pos + 1);
    auto child = getChild(current);
    return child ? (remaining.empty() ? child : child->findChild(remaining)) : nullptr;
}

/* Methods to manage node order */

void Node::moveToFront() {
    if (!_previous) return;

    auto previous = _previous;
    auto next = _next;

    // Update the previous node
    if (previous->getPrevious()) {
        previous->getPrevious()->setNext(shared_from_this());
    } else {
        _parent->_firstChild = shared_from_this();
    }

    previous->setNext(next);
    setPrevious(previous->getPrevious());

    // Update the next node
    if (next) {
        next->setPrevious(previous);
    } else {
        _parent->_lastChild = previous;
    }

    setNext(previous);
    previous->setPrevious(shared_from_this());
}

void Node::moveToBack() {
    if (!_next) return;

    auto previous = _previous;
    auto next = _next;

    // Update the next node
    if (next->getNext()) {
        next->getNext()->setPrevious(shared_from_this());
    } else {
        _parent->_lastChild = shared_from_this();
    }

    next->setPrevious(previous);
    setNext(next->getNext());

    // Update the previous node
    if (previous) {
        previous->setNext(next);
    } else {
        _parent->_firstChild = next;
    }

    setPrevious(next);
    next->setNext(shared_from_this());
}

void Node::moveToTop() {
    if (!_previous) return;

    auto previous = _previous;
    auto next = _next;

    if (next) {
        next->setPrevious(previous);
    } else {
        _parent->_lastChild = previous;
    }

    if (previous) {
        previous->setNext(next);
    }

    setPrevious(nullptr);
    setNext(_parent->_firstChild);

    if (_parent->_firstChild) {
        _parent->_firstChild->setPrevious(shared_from_this());
    }

    _parent->_firstChild = shared_from_this();
}

void Node::moveToBottom() {
    if (!_next) return;

    auto previous = _previous;
    auto next = _next;

    if (previous) {
        previous->setNext(next);
    } else {
        _parent->_firstChild = next;
    }

    if (next) {
        next->setPrevious(previous);
    }

    setNext(nullptr);
    setPrevious(_parent->_lastChild);

    if (_parent->_lastChild) {
        _parent->_lastChild->setNext(shared_from_this());
    }

    _parent->_lastChild = shared_from_this();
}

#include "Node.hpp"
#include <iostream>
#include <vector>
#include "Logger.hpp"

// Constructor
Node::Node(const std::string &name) 
    : _name(name),
      _id(generateId()),
      _childCount(0) {}

// Destructor
Node::~Node() {
    deleteAllChildren();
}

size_t Node::generateId() {
    static size_t id = 0;
    return ++id;
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

size_t Node::getId() const {
    return _id;
}

std::shared_ptr<Node> Node::getParent() const {
    return _parent.lock();
}

std::shared_ptr<Node> Node::getFirstChild() const {
    return _firstChild;
}

std::shared_ptr<Node> Node::getLastChild() const {
    return _lastChild;
}

std::shared_ptr<Node> Node::getPrevious() const {
    return _previous.lock();
}

std::shared_ptr<Node> Node::getNext() const {
    return _next;
}

/* Methods to manage children */

bool Node::insertChildToTop(std::shared_ptr<Node> child) {
    if (!child) return false;
    removeChild(child);

    child->setParent(shared_from_this());

    if (!_firstChild) {
        _firstChild = child;
        _lastChild = child;
    } else {
        _firstChild->setPrevious(child);
        child->setNext(_firstChild);
        _firstChild = child;
    }
    _childCount++;
    return true;
}

bool Node::insertChildToBottom(std::shared_ptr<Node> child) {
    if (!child) return false;
    removeChild(child);
    
    child->setParent(shared_from_this());

    if (!_firstChild) {
        _firstChild = child;
        _lastChild = child;
    } else {
        _lastChild->setNext(child);
        child->setPrevious(_lastChild);
        _lastChild = child;
    }
    _childCount++;
    return true;
}

bool Node::insertChild(std::shared_ptr<Node> child, size_t index) {
    if (!child) return false;
    removeChild(child);
    
    if (index < _childCount) {
        auto node = getChildByIndex(index);
        child->setNext(node);
        child->setPrevious(node->getPrevious());
        node->setPrevious(child);
        if (child->getPrevious()) {
            child->getPrevious()->setNext(child);
        }
        return true;
    }
    return false;
}

void Node::removeChild(std::shared_ptr<Node> child) {
    if (!child || _childCount == 0) return;
    if (child->getParent().get() != this) return;

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
    _childCount--;
}

void Node::deleteAllChildren() {
    while (_firstChild) {
        removeChild(_firstChild);
        _firstChild.reset();
    }
}

size_t Node::getChildCount() const {
    return _childCount;
}

// Method to get child by name
std::shared_ptr<Node> Node::getChildByName(const std::string &name) {
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

std::shared_ptr<Node> Node::getChildByIndex(size_t index) {
    if (_childCount == 0) return nullptr;
    if (index >= _childCount) return nullptr;
    if (index == 0) return _firstChild;
    if (index == _childCount - 1) return _lastChild;

    auto child = _firstChild;
    size_t ind = 0;
    while (child) {
        if (ind == index) {
            return child;
        }
        child = child->getNext();
        ind++;
    }
    return nullptr;
}

std::shared_ptr<Node> Node::getChildByID(size_t id) {
    if (_childCount == 0) return nullptr;

    auto child = _firstChild;
    while (child) {
        if (child->getId() == id) {
            return child;
        }
        child = child->getNext();
    }
    return nullptr;
}

// Method to find child by path
std::shared_ptr<Node> Node::getNodeByPath(const std::string &path) {
    if (_childCount == 0 || path.empty()) return nullptr;

    // token the path by '/'
    std::vector<std::string> tokens;
    std::string token;
    for (char c : path) {
        if (c == '/') {
            tokens.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }

    // search for the node
    std::shared_ptr<Node> current = nullptr;
    for (auto &token : tokens) {
        if (token.empty()) continue;
        if (token == "@" ) { // get root node
            if (!current) {
                current = getRootNode();
            } else {
                current = current->getParent();
            }
        } else if (token == "..") { // go up one level
            if (!current) {
                LOG(Warning) << "Invalid path '" << path << "'";
                return nullptr;
            } else {
                current = current->getParent();
                if (!current) {
                    LOG(Warning) << "Invalid path '" << path << "'";
                    return nullptr;
                }
            }
        } else if (token == ".") { // stay on the same node
            current = shared_from_this();
        } else { // get child node
            if (!current) {
                LOG(Warning) << "Invalid path '" << path << "'";
                return nullptr;
            }
            current = current->getChildByName(token);
            if (!current) {
                LOG(Warning) << "Invalid path '" << path << "'";
                return nullptr;
            }
        }
    }
    return current;
}

static std::shared_ptr<Node> _getNodeByID(std::shared_ptr<Node> node, const size_t id) {
    if (node->getId() == id) {
        return node;
    }
    if (node->getChildCount() == 0) return nullptr;

    auto child = node->getFirstChild();
    while (child) {
        if (child->getId() == id) {
            break;
        } else {
            child = _getNodeByID(child, id);
        }
        child = child->getNext();
    }
    return child;
}

std::shared_ptr<Node> Node::getNodeByID(const size_t id) {
    if (_childCount == 0) return nullptr;

    auto root = getRootNode();
    if (root->getId() == id) {
        return root;
    }
    return _getNodeByID(root, id);
}

std::shared_ptr<Node> Node::getRootNode() {
    if (auto parent = _parent.lock()) {
        return parent->getRootNode();
    }
    return shared_from_this();
}

/* Methods to manage node order */

void Node::moveToFront() {
    if (!_previous.lock()) return;

    auto previous = _previous.lock();
    auto next     = _next;

    // Update the previous node
    if (auto prevPrev = previous->getPrevious()) {
        prevPrev->setNext(shared_from_this());
    } else {
        _parent.lock()->_firstChild = shared_from_this();
    }

    previous->setNext(next);
    setPrevious(previous->getPrevious());

    // Update the next node
    if (next) {
        next->setPrevious(previous);
    } else {
        _parent.lock()->_lastChild = previous;
    }

    setNext(previous);
    previous->setPrevious(shared_from_this());
}

void Node::moveToBack() {
    if (!_next) return;

    auto previous = _previous.lock();
    auto next = _next;

    // Update the next node
    if (auto nextNext = next->getNext()) {
        nextNext->setPrevious(shared_from_this());
    } else {
        _parent.lock()->_lastChild = shared_from_this();
    }

    next->setPrevious(previous);
    setNext(next->getNext());

    // Update the previous node
    if (previous) {
        previous->setNext(next);
    } else {
        _parent.lock()->_firstChild = next;
    }

    setPrevious(next);
    next->setNext(shared_from_this());
}

void Node::moveToTop() {
    if (!_previous.lock()) return;

    auto previous = _previous.lock();
    auto next = _next;

    if (next) {
        next->setPrevious(previous);
    } else {
        _parent.lock()->_lastChild = previous;
    }

    if (previous) {
        previous->setNext(next);
    }

    setPrevious(nullptr);
    setNext(_parent.lock()->_firstChild);

    if (_parent.lock()->_firstChild) {
        _parent.lock()->_firstChild->setPrevious(shared_from_this());
    }

    _parent.lock()->_firstChild = shared_from_this();
}

void Node::moveToBottom() {
    if (!_next) return;

    auto previous = _previous.lock();
    auto next = _next;

    if (previous) {
        previous->setNext(next);
    } else {
        _parent.lock()->_firstChild = next;
    }

    if (next) {
        next->setPrevious(previous);
    }

    setNext(nullptr);
    setPrevious(_parent.lock()->_lastChild);

    if (_parent.lock()->_lastChild) {
        _parent.lock()->_lastChild->setNext(shared_from_this());
    }

    _parent.lock()->_lastChild = shared_from_this();
}

bool Node::moveToIndex(size_t index) {
    if (!_parent.lock()) return false;
    if (_parent.lock()->_childCount == 0) return false;

    if (index == 0) {
        moveToTop();
    } else if (index == _parent.lock()->_childCount - 1) {
        moveToBottom();
    } else if (index < _parent.lock()->_childCount) {
        insertChild(shared_from_this(), index);
    }
    return true;
}

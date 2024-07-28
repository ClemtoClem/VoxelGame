#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <memory>

class Node : public std::enable_shared_from_this<Node> {
public:
    /// @brief Constructor
    /// @param[in] name The name of the node
    Node(const std::string &name);

    /// @brief Destructor
    virtual ~Node();

/* Setters */

protected:
    /// @brief Set the name of the node
    /// @param[in] name The name of the node
    void setName(const std::string &name);

    /// @brief Set the parent of the node
    /// @param[in] parent The parent of the node
    void setParent(std::shared_ptr<Node> parent);

    /// @brief Set the previous sibling of the node
    /// @param[in] previous The previous sibling of the node
    void setPrevious(std::shared_ptr<Node> previous);

    /// @brief Set the next sibling of the node
    /// @param[in] next The next sibling of the node
    void setNext(std::shared_ptr<Node> next);

/* Getters */

public:
    /// @brief Get the name of the node
    /// @return The name of the node
    const std::string &getName() const;

    /// @brief Get the parent of the node
    /// @return The parent of the node
    std::shared_ptr<Node> getParent() const;

    /// @brief Get the first child of the node
    /// @return The first child of the node
    std::shared_ptr<Node> getFirstChild() const;

    /// @brief Get the last child of the node
    /// @return The last child of the node
    std::shared_ptr<Node> getLastChild() const;

    /// @brief Get the previous sibling of the
    /// @return The previous sibling of the node
    std::shared_ptr<Node> getPrevious() const;

    /// @brief Get the next sibling of the node
    /// @return The next sibling of the node
    std::shared_ptr<Node> getNext() const;

/* Methods to manage children */

    /// @brief Add a child to the node
    /// @param[in] child The child to add
    /// @return True if the child was added, false otherwise
    bool addChild(std::shared_ptr<Node> child);

    /// @brief Remove a child from the node
    /// @param[in] child The child to remove
    void removeChild(std::shared_ptr<Node> child);

    /// @brief Remove all children from the node
    void removeAllChildren();

    /// @brief Get the number of children of the node
    /// @return The number of children of the node
    size_t getChildCount() const;

    /// @brief Detach a child from the node
    /// @param[in] child The child to detach
    /// @return The child that was detached, or nullptr if not found
    std::shared_ptr<Node> detachChild(const std::string &name);

    /// @brief Method to get child by name
    /// @param[in] name The name of the child to find
    /// @return The child with the given name, or nullptr if not found
    std::shared_ptr<Node> getChild(const std::string &name);

    /// @brief Method to find child by path
    /// @param[in] path The path to the child to find
    /// @return The child with the given path, or nullptr if not found
    std::shared_ptr<Node> findChild(const std::string &path);

/* Methods to manage node order */

    /// @brief Move the node to the front of the list of children
    void moveToFront();

    /// @brief Move the node to the back of the list of children
    void moveToBack();

    /// @brief Move the node to the top of the list of children
    void moveToTop();

    /// @brief Move the node to the bottom of the list of children
    void moveToBottom();


private:
    std::string _name;

    std::shared_ptr<Node> _parent;
    std::shared_ptr<Node> _firstChild;
    std::shared_ptr<Node> _lastChild;
    size_t _childCount;

    std::shared_ptr<Node> _previous;
    std::shared_ptr<Node> _next;
};

#endif // NODE_HPP

#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <memory>
#include <vector>

class Node : public std::enable_shared_from_this<Node> {
public:
    /// @brief Constructor
    /// @param[in] name The name of the node
    Node(const std::string &name);

    /// @brief Destructor
    virtual ~Node();

    static size_t generateId();

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

    /// @brief Get the id of the node
    /// @return The id of the node
    size_t getId() const;

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
    bool insertChildToTop(std::shared_ptr<Node> child);

    /// @brief Add a child to the node
    /// @param[in] child The child to add
    /// @return True if the child was added, false otherwise
    bool insertChildToBottom(std::shared_ptr<Node> child);

    /// @brief Move the node to the previous sibling of the list of children
    /// @param[in] previous The previous sibling of the node to move to
    bool insertChild(std::shared_ptr<Node> child, size_t index);

    /// @brief Remove a child from the node
    /// @param[in] child The child to remove
    void removeChild(std::shared_ptr<Node> child);

    /// @brief Delete all children from the node
    void deleteAllChildren();

    /// @brief Get the number of children of the node
    /// @return The number of children of the node
    size_t getChildCount() const;

    /// @brief Method to get child by name
    /// @param[in] name The name of the child to find
    /// @return The child with the given name, or nullptr if not found
    std::shared_ptr<Node> getChildByName(const std::string &name);

    /// @brief Method to get child by index
    /// @param[in] index The index of the child to find
    /// @return The child with the given index, or nullptr if not found
    std::shared_ptr<Node> getChildByIndex(size_t index);

    /// @brief Method to find child by ID
    /// @param[in] id The ID of the child to find
    /// @return The child with the given ID, or nullptr if not found
    std::shared_ptr<Node> getChildByID(size_t id);

    /// @brief Method to find node by path
    /// @param[in] path The path of the node to find
    /// @return The node with the given path, or nullptr if not found
    std::shared_ptr<Node> getNodeByPath(const std::string &path);

    /// @brief Method to find node by ID
    /// @param[in] id The ID of the node to find
    /// @return The node with the given ID, or nullptr if not found
    std::shared_ptr<Node> getNodeByID(const size_t id);

    /// @brief Get the root node of the tree
    /// @return The root node of the tree
    std::shared_ptr<Node> getRootNode();

/* Methods to manage node order */

    /// @brief Move the node to the front of the list of children
    void moveToFront();

    /// @brief Move the node to the back of the list of children
    void moveToBack();

    /// @brief Move the node to the top of the list of children
    void moveToTop();

    /// @brief Move the node to the bottom of the list of children
    void moveToBottom();

    /// @brief Move the node to the index of the list of children
    /// @param[in] index The index of the node to move to
    bool moveToIndex(size_t index);

private:
    std::string _name;
    size_t _id;

    std::weak_ptr<Node> _parent;
    std::shared_ptr<Node> _firstChild;
    std::shared_ptr<Node> _lastChild;

    std::weak_ptr<Node> _previous;
    std::shared_ptr<Node> _next;

    size_t _childCount;
};

#endif // NODE_HPP

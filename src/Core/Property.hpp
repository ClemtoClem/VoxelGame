#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <variant>
#include <string>

// BaseProperty definition as provided
class BaseProperty {
public:
    enum class Access {
        READ_ONLY,
        WRITE_ONLY,
        READ_WRITE
    };

    virtual ~BaseProperty() {}
    virtual const std::string &getName() const = 0;

    virtual Access getAccess() const = 0;
    virtual bool isReadable() const = 0;
    virtual bool isWritable() const = 0;

    virtual std::string toString() const = 0;
};

// Property template class definition
template <typename T, typename ValueType>
class Property : public BaseProperty {
public:
    Property(const std::string &name, Access access = Access::READ_WRITE, const ValueType &value);
    ~Property();

    const std::string &getName() const override;

    ValueType &getValue();
    void setValue(ValueType value);

    Access getAccess() const override;
    bool isReadable() const override;
    bool isWritable() const override;

    std::string toString() const override;

private:
    std::string _name;
    Access _access;
    ValueType _value;
};

#endif // PROPERTY_HPP
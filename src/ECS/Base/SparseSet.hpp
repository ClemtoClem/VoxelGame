#ifndef ECS_BASE_SPARSESET_HPP
#define ECS_BASE_SPARSESET_HPP

#include <vector>
#include <tuple>
#include <limits>
#include <stdexcept>

namespace ecs {

template<typename Id, typename T>
class SparseSet {
    static constexpr auto Undefined = std::numeric_limits<std::size_t>::max();

public:
    template<typename ...Args>
    std::tuple<Id, T&> emplace(Args&& ...args) {
        std::size_t i = mObjects.size();
        T& object = mObjects.emplace_back(std::forward<Args>(args)...);

        Id id;
        if (mFreeIds.empty()) {
            id = static_cast<Id>(mIdToIndex.size());
            mIdToIndex.push_back(i);
        } else {
            id = mFreeIds.back();
            mFreeIds.pop_back();
            mIdToIndex[static_cast<std::size_t>(id)] = i;
        }

        mIndexToId.push_back(id);
        return std::make_tuple(id, object);
    }

    bool has(Id id) const {
        if (static_cast<std::size_t>(id) >= mIdToIndex.size())
            return false;
        return mIdToIndex[static_cast<std::size_t>(id)] != Undefined;
    }

    T& get(Id id) {
        if (!has(id)) {
            throw std::out_of_range("Invalid ID provided");
        }
        return mObjects[mIdToIndex[static_cast<std::size_t>(id)]];
    }

    const T& get(Id id) const {
        if (!has(id)) {
            throw std::out_of_range("Invalid ID provided");
        }
        return mObjects[mIdToIndex[static_cast<std::size_t>(id)]];
    }

    void erase(Id id) {
        if (!has(id)) return;

        std::size_t i = mIdToIndex[static_cast<std::size_t>(id)];

        std::size_t lastIdx = mObjects.size() - 1;
        if (i != lastIdx) {
            std::swap(mObjects[i], mObjects.back());
            Id lastObjectId = mIndexToId[lastIdx];
            mIdToIndex[static_cast<std::size_t>(lastObjectId)] = i;
            mIndexToId[i] = lastObjectId;
        }

        mObjects.pop_back();
        mIndexToId.pop_back();
        mIdToIndex[static_cast<std::size_t>(id)] = Undefined;
        mFreeIds.push_back(id);
    }

    void shrink_to_fit() {
        mObjects.shrink_to_fit();
        mIdToIndex.shrink_to_fit();
        mIndexToId.shrink_to_fit();
        mFreeIds.shrink_to_fit();
    }

    std::vector<T>& getObjects() {
        return mObjects;
    }

    const std::vector<T>& getObjects() const {
        return mObjects;
    }

    std::size_t getSize() const {
        return mObjects.size();
    }

    void reserve(std::size_t size) {
        mIdToIndex.reserve(size);
        mFreeIds.reserve(size);
        mObjects.reserve(size);
        mIndexToId.reserve(size);
    }

private:
    std::vector<std::size_t> mIdToIndex;
    std::vector<Id> mFreeIds;
    std::vector<T> mObjects;
    std::vector<Id> mIndexToId;
};

} // namespace ecs

#endif // ECS_BASE_SPARSESET_HPP

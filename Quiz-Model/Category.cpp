#include "Category.hpp"

Category::Category(const QString &name, const QString &parentName) {
    mName = name;
    mParentName = parentName;
}

void Category::setName(const QString &name) {
    mName = name;
}

QString Category::getName() const {
    return mName;
}

void Category::setParentName(const QString &parentName) {
    mParentName = parentName;
}

QString Category::getParentName() const {
    return mParentName;
}

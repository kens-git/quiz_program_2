#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <QString>

#include "quiz-model_global.h"

class QUIZMODELSHARED_EXPORT Category {
    public:
        Category() = default;
        Category(const QString& name, const QString& parentName = "root");

        void setName(const QString& name);
        QString getName() const;

        void setParentName(const QString& parentName);
        QString getParentName() const;

    private:
        QString mName;
        QString mParentName;
};

#endif // CATEGORY_HPP

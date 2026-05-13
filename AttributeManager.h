#ifndef ATTRIBUTEMANAGER_H
#define ATTRIBUTEMANAGER_H

#include <QObject>

class AttributeManager : public QObject
{
    Q_OBJECT

public:
    static AttributeManager& getInstance();

    void addSleep(int value);
    void addWisdom(int value);
    void addWarmth(int value);

    int getSleep() const { return m_sleep; }
    int getWisdom() const { return m_wisdom; }
    int getWarmth() const { return m_warmth; }

    void reset();

signals:
    void attributesChanged(int sleep, int wisdom, int warmth);

private:
    AttributeManager() = default;
    AttributeManager(const AttributeManager&) = delete;
    AttributeManager& operator=(const AttributeManager&) = delete;

private:
    int m_sleep = 0;
    int m_wisdom = 0;
    int m_warmth = 0;
};

#endif
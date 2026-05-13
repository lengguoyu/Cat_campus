#include "AttributeManager.h"
#include <QDebug>

AttributeManager& AttributeManager::getInstance()
{
    static AttributeManager instance;
    return instance;
}

void AttributeManager::addSleep(int value)
{
    m_sleep += value;
    if (m_sleep < 0) m_sleep = 0;
    emit attributesChanged(m_sleep, m_wisdom, m_warmth);
    qDebug() << "[属性] 睡眠:" << m_sleep << "| 智慧:" << m_wisdom << "| 暖心:" << m_warmth;
}

void AttributeManager::addWisdom(int value)
{
    m_wisdom += value;
    if (m_wisdom < 0) m_wisdom = 0;
    emit attributesChanged(m_sleep, m_wisdom, m_warmth);
    qDebug() << "[属性] 睡眠:" << m_sleep << "| 智慧:" << m_wisdom << "| 暖心:" << m_warmth;
}

void AttributeManager::addWarmth(int value)
{
    m_warmth += value;
    if (m_warmth < 0) m_warmth = 0;
    emit attributesChanged(m_sleep, m_wisdom, m_warmth);
    qDebug() << "[属性] 睡眠:" << m_sleep << "| 智慧:" << m_wisdom << "| 暖心:" << m_warmth;
}

void AttributeManager::reset()
{
    m_sleep = 0;
    m_wisdom = 0;
    m_warmth = 0;
    emit attributesChanged(m_sleep, m_wisdom, m_warmth);
}
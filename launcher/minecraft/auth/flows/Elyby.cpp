#include "Elyby.h"

#include "minecraft/auth/steps/ElybyStep.h"
#include "minecraft/auth/steps/ElybyProfileStep.h"
#include "minecraft/auth/steps/GetSkinStep.h"

ElybyRefresh::ElybyRefresh(
    AccountData *data,
    QObject *parent
) : AuthFlow(data, parent) {
    m_steps.append(makeShared<ElybyStep>(m_data, QString()));
    m_steps.append(makeShared<ElybyProfileStep>(m_data));
    m_steps.append(makeShared<GetSkinStep>(m_data));
}

ElybyLogin::ElybyLogin(
    AccountData *data,
    QString password,
    QObject *parent
): AuthFlow(data, parent), m_password(password) {
    m_steps.append(makeShared<ElybyStep>(m_data, m_password));
    m_steps.append(makeShared<ElybyProfileStep>(m_data));
    m_steps.append(makeShared<GetSkinStep>(m_data));
}

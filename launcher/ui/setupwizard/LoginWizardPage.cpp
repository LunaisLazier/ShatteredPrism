#include "LoginWizardPage.h"
#include "minecraft/auth/AccountList.h"
#include "ui/dialogs/MSALoginDialog.h"
#include "ui_LoginWizardPage.h"
#include "ui/dialogs/AuthlibInjectorLoginDialog.h"
#include "ui/dialogs/OfflineLoginDialog.h"


#include "Application.h"

LoginWizardPage::LoginWizardPage(QWidget* parent) : BaseWizardPage(parent), ui(new Ui::LoginWizardPage)
{
    ui->setupUi(this);
}

LoginWizardPage::~LoginWizardPage()
{
    delete ui;
}

void LoginWizardPage::initializePage() {}

bool LoginWizardPage::validatePage()
{
    return true;
}

void LoginWizardPage::retranslate()
{
    ui->retranslateUi(this);
}

void LoginWizardPage::on_MSAButton_clicked()
{
    wizard()->hide();
    auto account = MSALoginDialog::newAccount(nullptr);
    wizard()->show();
    if (account) {
        APPLICATION->accounts()->addAccount(account);
        APPLICATION->accounts()->setDefaultAccount(account);
        if (wizard()->currentId() == wizard()->pageIds().last()) {
            wizard()->accept();
        } else {
            wizard()->next();
        }
    }
}

void LoginWizardPage::on_authlibButton_clicked()
{
    wizard()->hide();
    auto account = AuthlibInjectorLoginDialog::newAccount(
        this, tr("Please enter your username (sometimes an email address), password, and the URL of your API server."
                 "<br>"
                 "See <a href=\"https://github.com/lunaislazier/ShatteredPrism/blob/develop/doc/alternative-auth-servers.md\">this page</a> in "
                 "the Shattered Prism repository for a list of common API servers."
                 "<br><br>"
                 "<b>Caution!</b> Your username and password will be sent to the authentication server you specify!"));
    wizard()->show();
    if (account) {
        APPLICATION->accounts()->addAccount(account);
        APPLICATION->accounts()->setDefaultAccount(account);
        if (wizard()->currentId() == wizard()->pageIds().last()) {
            wizard()->accept();
        } else {
            wizard()->next();
        }
    }
}

void LoginWizardPage::on_offlineButton_clicked()
{
    wizard()->hide();
    auto account = OfflineLoginDialog::newAccount(nullptr, "Please enter your desired username to add your offline account.");
    wizard()->show();
    if (account) {
        APPLICATION->accounts()->addAccount(account);
        APPLICATION->accounts()->setDefaultAccount(account);
        if (wizard()->currentId() == wizard()->pageIds().last()) {
            wizard()->accept();
        } else {
            wizard()->next();
        }
    }
}
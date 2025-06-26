#pragma once
#include <QWidget>
#include "BaseWizardPage.h"

namespace Ui {
class LoginWizardPage;
}

class LoginWizardPage : public BaseWizardPage {
    Q_OBJECT

   public:
    explicit LoginWizardPage(QWidget* parent = nullptr);
    ~LoginWizardPage();

    void initializePage() override;
    bool validatePage() override;
    void retranslate() override;
   private slots:
    void on_MSAButton_clicked();
    void on_authlibButton_clicked();
    void on_offlineButton_clicked();

   private:
    Ui::LoginWizardPage* ui;
};

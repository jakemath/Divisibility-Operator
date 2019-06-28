#ifndef bigint_application
#define bigint_application

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include "bigint.h"

class BigintApplication : public Wt::WApplication
{
public:
    BigintApplication(const Wt::WEnvironment& env);
private:
    Wt::WLineEdit *dividend_size_edit;
    Wt::WLineEdit *divisor_size_edit;
    Wt::WText *dividend;
    Wt::WText *divisor;
    Wt::WText *print;
    void print_output();
};

#endif

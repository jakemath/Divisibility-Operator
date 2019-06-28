#include "bigint_application.h"

BigintApplication::BigintApplication (const Wt::WEnvironment& env)
: Wt::WApplication(env)
{
    setTitle("Divisibility Operator");
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("Enter the number of digits for dividend and divisor."));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("Dividend digits must be > divisor digits."));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("The program will generate a random operand & "));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("divisor of your specified size, multiply the "));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("two to generate a dividend of approximately the size "));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("you specified, then run the divisibility operator."));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>(" A return value of 1 indicates a correct result."));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    // Dividend
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("Dividend size: "));
    dividend_size_edit = root() -> addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    // Divisor
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("Divisor size: "));
    divisor_size_edit = root() -> addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>());
    // Button to start computation and compose output
    auto compute = root() -> addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Compute"));
    //print = root() -> addWidget(Wt::cpp14::make_unique<Wt::WText());
    compute -> clicked().connect(this, &BigintApplication::print_output);
}

void BigintApplication::print_output()
{
    
    unsigned long long d = std::stoull(dividend_size_edit -> text());
    unsigned long long divsr_size = std::stoull(divisor_size_edit -> text());
    unsigned long long a_size;
    if (d < divsr_size)
    {
        root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
        root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
        root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("Dividend size must be >= divisor size"));
        return;
    }
    else if (d == divsr_size)
        a_size = 1;
    else
        a_size = d - divsr_size;
    bigint a(a_size, 1), b(divsr_size, 1);
    // Check for faulty inputs
    short odds[4] = {3,7,9,1};
    if (b.get_data().front() % 2 == 0)
    {
        srand(time(0));
        if (b.get_data().size() > 1)
            b.get_data().front() = odds[rand() % 4];
        else if (b.get_data().size() == 1 && b.get_data().front() != 2)
            b.get_data().front() = odds[rand() % 3];
    }
    else if (b.get_data().front() == 5 && b.get_data().size() > 1)
        b.get_data().front() = odds[rand() % 4];
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    a = a * b;
    output r = div(a,b);
    // a div b:
    std::wstring w1,w2;
    w1.assign(r.dividend.begin(),r.dividend.end());
    w2.assign(r.divisor.begin(), r.divisor.end());
    dividend = root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>());
    dividend -> setWordWrap(true);
    dividend -> setText(Wt::WString(w1));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>(" div "));
    divisor = root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>());
    divisor -> setWordWrap(true);
    divisor -> setText(Wt::WString(w2));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>(":"));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    // return value:
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("Return value: " + Wt::WString(std::to_wstring(r.return_val))));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    // digits in dividend:
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("Digits in dividend: " + Wt::WString(std::to_wstring(r.dividend_size))));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    // digits in divisor:
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("Digits in divisor: " + Wt::WString(std::to_wstring(r.divisor_size))));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
    // runtime:
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>("Runtime: " + Wt::WString(std::to_wstring(r.runtime))));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WText>(" ms"));
    root() -> addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
}

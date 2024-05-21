#include "test.hpp"

int main()
{
    Test::ValuesTest();
    Test::ExpressionTest();
    Test::EnvTest();
    Test::AdditionTest();
    Test::AdditionMatrixTest();
    Test::SubtractionTest();
    Test::MultiplicationTest();
    Test::MultiplicationMatrixTest();
    Test::DivisionTest();
    Test::PowerTest();
    Test::SquareRootTest();
    Test::RootTest();
    Test::TrigonometricsTest();
    Test::InverseMatrixTest();
    Test::MatrixLUTest();
    Test::TridiagonalMatrixTest();
    Test::RealEigenvaluesTest();
    Test::DeterminantTest();
    Test::DivisionMatrixTest();
    Test::IntegralTest();
    Test::InterpolateTest();
    Test::ODEFirstOrderInitialValuesTest();
    Test::FindRootBisectionTest();
    return 0;
}
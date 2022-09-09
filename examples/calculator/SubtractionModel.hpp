#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <QtNodes/NodeDelegateModel>

#include "MathOperationDataModel.hpp"

#include "DecimalData.hpp"

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class SubtractionModel : public MathOperationDataModel
{
public:

  virtual
  ~SubtractionModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("Subtraction"); }

  virtual bool
  portCaptionVisible(PortType portType, PortIndex portIndex) const override
  {
    Q_UNUSED(portType); Q_UNUSED(portIndex);
    return true;
  }


  virtual QString
  portCaption(PortType portType, PortIndex portIndex) const override
  {
    switch (portType)
    {
      case PortType::In:
        if (portIndex == 0)
          return QStringLiteral("Minuend");
        else if (portIndex == 1)
          return QStringLiteral("Subtrahend");

        break;

      case PortType::Out:
        return QStringLiteral("Result");

      default:
        break;
    }
    return QString();
  }


  QString
  name() const override
  { return QStringLiteral("Subtraction"); }

private:

  void
  compute() override
  {
    PortIndex const outPortIndex = 0;

    auto n1 = _number1.lock();
    auto n2 = _number2.lock();

    if (n1 && n2)
    {
      _result = std::make_shared<DecimalData>(n1->number() -
                                              n2->number());
    }
    else
    {
      _result.reset();
    }

    Q_EMIT dataUpdated(outPortIndex);
  }


};

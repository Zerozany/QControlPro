_Pragma("once");
#include <QWidget>
#include <functional>
#include <memory>

class WidgetManager : public QObject
{
    Q_OBJECT
public:
    explicit(true) WidgetManager(QMap<QString, QWidget*>& _widgetsmap, QWidget* _widget, QObject* _parent = nullptr);
    WidgetManager(const WidgetManager& /*other*/)                = delete;
    WidgetManager& operator=(const WidgetManager& /*other*/)     = delete;
    WidgetManager(WidgetManager&& /*other*/) noexcept            = delete;
    WidgetManager& operator=(WidgetManager&& /*other*/) noexcept = delete;
    ~WidgetManager()                                             = default;

    auto getWidget(const QString& _name) noexcept -> QWidget*;

private:
    auto setParent(QWidget* _widget) noexcept -> void;

private:
    QMap<QString, QWidget*>& m_widgetsmap;
};

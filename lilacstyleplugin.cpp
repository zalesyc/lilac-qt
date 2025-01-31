#include "lilacstyleplugin.h"
#include <QStringList>
#include <QStringLiteral>
#include "lilacstyle.h"

namespace Lilac {
QStyle* StylePlugin::create(const QString& key) {
    if (key.compare(QLatin1String("lilac"), Qt::CaseInsensitive) == 0) {
        return new Style;
    }
    return nullptr;
}

QStringList StylePlugin::keys() const {
    return QStringList(QStringLiteral("Lilac"));
}
}  // namespace Lilac

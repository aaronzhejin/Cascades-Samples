/* Copyright (c) 2012 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "Messages.hpp"

#include "MessageComposer.hpp"
#include "MessageViewer.hpp"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/pim/message/MessageUpdate>

#include <QLocale>
#include <QTranslator>

using namespace bb::cascades;

Q_DECLARE_METATYPE(bb::pim::message::MessageUpdate)

Q_DECL_EXPORT int main(int argc, char **argv)
{
//! [0]
    // Register our custom types with QML, so that they can be used as property types
    qmlRegisterUncreatableType<MessageComposer>("com.example.bb10samples.pim.messages", 1, 0, "MessageComposer", "Usage as property type and access to enums");
    qmlRegisterType<MessageViewer>();
//! [0]

    qRegisterMetaType<bb::pim::message::MessageFolderKey>();
    qRegisterMetaType<bb::pim::message::MessageUpdate>();

    Application app(argc, argv);

    // localization support
    QTranslator translator;
    const QString locale_string = QLocale().name();
    const QString filename = QString::fromLatin1("messages_%1").arg(locale_string);
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator(&translator);
    }

//! [1]
    // Load the UI description from main.qml
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(&app);

    // Make the Messages object available to the UI as context property
    qml->setContextProperty("_messages", new Messages(&app));
//! [1]

    // Create the application scene
    AbstractPane *appPage = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(appPage);

    return Application::exec();
}

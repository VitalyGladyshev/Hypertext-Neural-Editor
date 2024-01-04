#include "aichat.h"
#include "ui_aichat.h"
#include "settings.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

AIChat::AIChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AIChat),
    _currentLLM(AIModels::GigaChat)
{
    ui->setupUi(this);

    _pNetworkInterface = new QNetworkAccessManager(this);

    connect(ui->pushButtonProperties, SIGNAL(clicked(bool)),
            this, SLOT(SlotPropertiesButtonClicked()));
    connect(ui->pushButtonSend, SIGNAL(clicked(bool)),
            this, SLOT(SlotSendButtonClicked()));
    connect(_pNetworkInterface, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(SlotReceptionFinished(QNetworkReply*)));
}

AIChat::~AIChat()
{
    delete ui;
}

// Задать текст клавиши "Настройки" для перевода
void AIChat::SetPropertiesButtonText(const QString buttonText)
{
    ui->pushButtonProperties->setText(buttonText);
}

// Задать текст клавиши "Отправить" для перевода
void AIChat::SetSendButtonText(const QString buttonText)
{
    ui->pushButtonSend->setText(buttonText);
}

// Слот на клик клавиши "Настройки"
void AIChat::SlotPropertiesButtonClicked()
{
    qDebug() << "PropertiesButtonClicked";
}

// Слот на клик клавиши "Отправить"
void AIChat::SlotSendButtonClicked()
{
    ui->textEditChat->append("Пользователь");
    ui->textEditChat->append(ui->textEditPrompt->toPlainText());
    ui->textEditChat->append("");

//    const QUrl authUrlAuth { "https://ngw.devices.sberbank.ru:9443/api/v2/oauth" };
//    const QString authorization { "Bearer " + Settings::GetInstance().GetGigaChatAuthorization() };
//    const QString payload { "scope=GIGACHAT_API_PERS" };
//    qDebug() << authorization;

//    QNetworkRequest request(authUrlAuth);

//    request.setRawHeader("RqUID", "6f0b1291-c7f3-43c6-bb2e-9f3efb2dc98e");
//    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
//    request.setRawHeader("Authorization", authorization.toLocal8Bit());

//    _pNetworkInterface->post(request, payload.toLocal8Bit());

    const QUrl authUrlModels { QString("https://gigachat.devices.sberbank.ru/api/v1") + "/models" };
    const QString token { "Bearer eyJjdHkiOiJqd3QiLCJlbmMiOiJBMjU2Q0JDLUhTNTEyIiwiYWxnIjoiUlNBLU9BRVAtMjU2In0.S4sEgIZ7ii9L8dKZenYp9qaPzpCw6SUOsK38_ukYktfKSpnR-YBKqZKycWSfnO1c8YS2_RM2ldAoctxSpgxvTSTSizwp_Wt-4TJyR4yKDvwQRUCNMmB-KZx-j4XSFqkdMnxnHvhlJJlbPZu5naN7EatcQgmakABfAVHQllakyKK8pl3yTxW47DBEielfysR8trKwm4Rr6GFKZ9LKf7J8yB_NisfoCczq0UfmOYZ69f7df5EP7XdUsip--Lcy_yApZ2JnApDK0T5x8JH8PVMZy_x2yh21Ecb4yoPPahmr_kSuMC5HFbFWMJJ3BO6iP7DhKtSf_YvdEMf0ddxWlpVWWg.m1Tb4co_DG1QmW7UkfRUow.rWvVIlkwAWrWXQrI51fj3lcnM0PitkPhaSy-j7FndFU8p9C6vVt-hEVryZQS2UzV13uuQsY5lMFXY4DzuYnOLiMYPm9TqQDZfKPBHfc8wOhCLTJepjlWObuLwfDfXsIDSS6moOkipHQR_yLbg-9nHJnA7Z-QzUqnAsQ4ytWF4Vlq8neMvSwi4S-p3LYvRAVkVNvKa0_ZmLR_I0gpohKanHEhFB4pmBCZ_Vx9G_H03rgILB2bbQeolguvEM55_qXqYKGOdoRpqqb30sA6T9pAdET_zpcTot564harYLjwrO_BQJ_Si0dnsgT8OV7-_VFdJZveGZyfNJ-8sXGUUHpnCmA2ScgtB2X-bMJVGjcuMiZvDZi0Y3yNDFgmzjPFH2-LCiZumx_pMSf5dSUjDiGphpcT1DPydyz6pRBmo_O5cvsMyruDIIx0GwHzMrXKd_MqtKOqKLGDeChgdmcpyD48rXa7IqBThSl4FQS9o2BIHqtYBnnQ73aN6bkojpZJr-9P0W6vO8TzZiPzKnoEsVgS567AXWWm_xVXxB28_zub1EHUPxIdb49zR0wHDfqNGnlKNmK0-HG8kynCHkFx3w8OZmjtoDf7Y_E9Z6aeF8T9P_LGzpHhX-MQ5tM4iEkzRTRIYhAZyjghHVcYMLJXiUM5mKsDgeXfIR1bg-a9api8iYkuCi-e-pl6WzUXrw9Wof7KzIo_K6-i1XPUlgs6n28gy0sdoRxwAQyTNYza4seUXKg.W1BW0ikxOfkvwW-z8G04r1g4yT_zxy4njjDeAXC4nFQ" };
//    QNetworkRequest requestList(authUrlModels);
//    requestList.setRawHeader("Authorization", token.toLocal8Bit());

//    _pNetworkInterface->get(requestList);

    const QUrl authUrlCompletion { QString("https://gigachat.devices.sberbank.ru/api/v1") + "/chat/completions"};
    QJsonObject dataForMessage
    {
        {"model", "GigaChat:latest"},
        {"temperature", 0.87},
        {"top_p", 0.47},
        {"n", 1},
        {"max_tokens", 512},
        {"repetition_penalty", 1.07},
        {"stream", false},
        {"update_interval", 0},
    };
    QJsonObject systemMessage
    {
        {"role", "system"},
        {"content", "Отвечай как квалифицированный автор технической документации"}
    };
    QJsonObject userMessage
    {
        {"role", "user"},
        {"content", ui->textEditPrompt->toPlainText()}
    };
    QJsonArray messages;
    messages.append(systemMessage);
    messages.append(userMessage);
    dataForMessage["messages"] = messages;

    QJsonDocument jsonDocument(dataForMessage);

    qDebug() << jsonDocument.toJson(QJsonDocument::Compact);

    QNetworkRequest requestCompletion(authUrlCompletion);
    requestCompletion.setRawHeader("Content-Type", "application/json");
    requestCompletion.setRawHeader("Authorization", token.toLocal8Bit());

    _pNetworkInterface->post(requestCompletion, jsonDocument.toJson(QJsonDocument::Compact));

    ui->textEditPrompt->clear();
}

// Слот на окончание передачи
void AIChat::SlotReceptionFinished(QNetworkReply* pReply)
{
    auto replyData = pReply->readAll();
    ui->textEditChat->append("GigaChat");
    if (pReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "ReceptionFinished error!";

        qDebug() << pReply->rawHeaderList();
        qDebug() << pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug() << pReply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        qDebug() << pReply->errorString() << pReply->error();

        ui->textEditChat->append(QString(replyData));
        qDebug() << replyData;
    }
    else
    {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(replyData);
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["choices"].toArray();

        for(auto value: jsonArray)
        {
            QJsonObject objMessage = value.toObject();
            QJsonObject obj = objMessage["message"].toObject();
            ui->textEditChat->append(obj["content"].toString());
        }
    }

    ui->textEditChat->append("");
    pReply->deleteLater();
}

#include <QApplication>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 初始化随机数种子
    srand(time(nullptr));

    QFont font;
    font.setFamily("SimHei");
    font.setPointSize(9);
    a.setFont(font);

    // ========== 主窗口 ==========
    QWidget w;
    w.setWindowTitle("速算24-测试");
    w.resize(2560, 1500);
    w.setStyleSheet("background-color: #2b2b2b;");

    QVBoxLayout *mainLayout = new QVBoxLayout(&w);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // ========== 1. 顶部窄长条标题/信息框 ==========
    QWidget *topWidget = new QWidget;
    topWidget->setFixedHeight(120);
    topWidget->setStyleSheet("background-color: #e8e8e8; border-radius: 4px;");

    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(10, 0, 10, 0);

    QLabel *titleLabel = new QLabel("速算24 - 测试");
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: #333;");
    QLabel *infoLabel = new QLabel("附加信息：2025-12-28");
    infoLabel->setStyleSheet("font-size: 32px; color: #666;");

    topLayout->addWidget(titleLabel);
    topLayout->addStretch();
    topLayout->addWidget(infoLabel);

    mainLayout->addWidget(topWidget);

    // ========== 2. 中间宽条区域（保持原有样式） ==========
    QFrame *middleFrame = new QFrame;
    middleFrame->setStyleSheet(
        "background-color:#3c3c3c; border: 1px solid #ddd; border-radius: 4px;");
    middleFrame->setMinimumHeight(200);
    mainLayout->addWidget(middleFrame, 1);

    // ========== 3. 底部左中右区域 ==========
    QWidget *bottomWidget = new QWidget;
    bottomWidget->setFixedHeight(300);
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomWidget);
    bottomLayout->setSpacing(20);
    bottomLayout->setContentsMargins(10, 0, 10, 0);

    // 3.1 左侧：6个按钮（2行3列）
    QWidget *leftWidget = new QWidget;
    QGridLayout *leftLayout = new QGridLayout(leftWidget);
    leftLayout->setSpacing(10);

    QString buttonLabels[2][3] = {
        {"+", "-", "("},
        {"x", "/", ")"}
    };

    QString buttonColors[2][3] = {
        {"#f0f0f0", "#f0f0f0", "#2196F3"},
        {"#f0f0f0", "#f0f0f0", "#2196F3"}
    };

    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton *btn = new QPushButton(buttonLabels[row][col]);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            QString normalColor = buttonColors[row][col];
            QString hoverColor = (normalColor == "#2196F3") ? "#1976D2" : "#e0e0e0";

            QString style = QString("QPushButton { "
                                    "background-color: %1; "
                                    "color: %2; "
                                    "border: 1px solid #ccc; "
                                    "border-radius: 4px; "
                                    "font-size: 65px; "
                                    "font-weight: bold; "
                                    "}"
                                    "QPushButton:hover { "
                                    "background-color: %3; "
                                    "}")
                                .arg(normalColor)
                                .arg(normalColor == "#2196F3" ? "white" : "#333")
                                .arg(hoverColor);

            btn->setStyleSheet(style);
            leftLayout->addWidget(btn, row, col);
        }
        leftLayout->setRowStretch(row, 1);
    }

    for (int col = 0; col < 3; ++col) {
        leftLayout->setColumnStretch(col, 1);
    }

    leftWidget->setMinimumWidth(200);
    bottomLayout->addWidget(leftWidget, 1);

    // 3.2 中间：4张扑克牌容器区域
    QWidget *centerWidget = new QWidget;
    centerWidget->setStyleSheet("background-color: #3c3c3c; border-radius: 4px;");

    // 创建水平布局用于放置4个扑克牌容器
    QHBoxLayout *cardLayout = new QHBoxLayout(centerWidget);
    cardLayout->setSpacing(15);
    cardLayout->setContentsMargins(15, 15, 15, 15);

    // 创建4个扑克牌容器
    QVector<QLabel*> cardImageLabels;
    QVector<QLabel*> cardNumberLabels;

    for (int i = 0; i < 4; ++i) {
        // 扑克牌容器框架
        QFrame *cardFrame = new QFrame;
        cardFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QString frameStyle =
            "QFrame {"
            "   background-color: rgba(255, 255, 255, 0.05);"
            "   border: 3px dashed #666;"
            "   border-radius: 12px;"
            "}";

        cardFrame->setStyleSheet(frameStyle);

        // 创建内部布局
        QVBoxLayout *innerLayout = new QVBoxLayout(cardFrame);
        innerLayout->setSpacing(0);
        innerLayout->setContentsMargins(5, 5, 5, 5);

        // 扑克牌图片标签
        QLabel *cardImageLabel = new QLabel;
        cardImageLabel->setAlignment(Qt::AlignCenter);
        cardImageLabel->setScaledContents(true);
        cardImageLabel->setMinimumSize(80, 120);
        cardImageLabel->setText("?");
        cardImageLabel->setStyleSheet(
            "QLabel {"
            "   font-size: 80px;"
            "   font-weight: bold;"
            "   color: #aaa;"
            "   background-color: transparent;"
            "}");

        // 容器编号
        QLabel *cardNumberLabel = new QLabel(QString("牌%1").arg(i + 1));
        cardNumberLabel->setAlignment(Qt::AlignCenter);
        cardNumberLabel->setStyleSheet(
            "QLabel {"
            "   font-size: 14px;"
            "   color: #777;"
            "   background-color: transparent;"
            "}");

        innerLayout->addWidget(cardImageLabel, 1);
        innerLayout->addWidget(cardNumberLabel);

        cardLayout->addWidget(cardFrame);
        cardLayout->setStretch(i, 1);

        cardImageLabels.append(cardImageLabel);
        cardNumberLabels.append(cardNumberLabel);
    }

    bottomLayout->addWidget(centerWidget, 3);

    // 3.3 右侧："发牌→三个小按钮"切换逻辑
    QWidget *rightWidget = new QWidget;
    QVBoxLayout *rightOuterLayout = new QVBoxLayout(rightWidget);
    rightOuterLayout->setSpacing(10);

    // 发牌按钮
    QPushButton *dealCardBtn = new QPushButton("发牌");
    dealCardBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    dealCardBtn->setStyleSheet(
        "QPushButton { background-color: #2196F3; color: white; "
        "border: none; border-radius: 4px; font-size:48px; font-weight: bold; }"
        "QPushButton:hover { background-color: #1976D2; }");

    // 三个小按钮容器
    QWidget *smallBtnWidget = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(smallBtnWidget);
    rightLayout->setSpacing(10);

    QPushButton *rightBtn1 = new QPushButton("提交");
    QPushButton *rightBtn2 = new QPushButton("不存在答案");
    QPushButton *rightBtn3 = new QPushButton("重置");

    rightBtn1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rightBtn2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rightBtn3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    rightBtn1->setStyleSheet(
        "QPushButton { background-color: #4CAF50; color: "
        "white; border: none; border-radius: 4px; font-size:48px; }"
        "QPushButton:hover { background-color: #45a049; }");
    rightBtn2->setStyleSheet(
        "QPushButton { background-color:rgb(231, 249, 32); color: "
        "black; border: none; border-radius: 4px;font-size:48px; }"
        "QPushButton:hover { background-color:rgb(234, 223, 10); }");
    rightBtn3->setStyleSheet(
        "QPushButton { background-color:rgb(255, 0, 0); color: white; "
        "border: none; border-radius: 4px;font-size:48px; }"
        "QPushButton:hover { background-color:rgb(180, 0, 0); }");

    rightLayout->addWidget(rightBtn1);
    rightLayout->addWidget(rightBtn2);
    rightLayout->addWidget(rightBtn3);
    rightLayout->setStretch(0, 1);
    rightLayout->setStretch(1, 1);
    rightLayout->setStretch(2, 1);

    smallBtnWidget->hide();

    // 根据你提供的实际文件列表创建数组
    // 完全按照你提供的文件名
    QVector<QString> allCards = {
        // 梅花
        "Club2.gif", "Club3.gif", "Club4.gif", "Club5.gif", "Club6.gif", "Club7.gif",
        "Club8.gif", "Club9.gif", "Club10.gif", "ClubA.gif", "ClubJ.gif", "ClubQ.gif","ClubK.gif",
        // 方块
        "Diamond2.gif", "Diamond3.gif", "Diamond4.gif", "Diamond5.gif", "Diamond6.gif",
        "Diamond7.gif", "Diamond8.gif", "Diamond9.gif", "Diamond10.gif", "DiamondA.gif",
        "DiamondJ.gif", "DiamondK.gif", "DiamondQ.gif",
        // 红心（完全按照你提供的文件名）
        "Heart2.gif", "Heart3.gif", "Heart4.gif", "Heart5.gif", "Heart6.gif",
        "Heart7.gif", "Heart8.gif", "Heart9.gif", "Heart10.gif", "HeartA.gif",
        "HeartJ.gif", "HeartQ.gif", "HeartK.gif",
        // 黑桃
        "Spade2.gif", "Spade3.gif", "Spade4.gif", "Spade5.gif", "Spade6.gif",
        "Spade7.gif", "Spade8.gif", "Spade9.gif", "Spade10.gif", "SpadeA.gif",
        "SpadeJ.gif", "SpadeK.gif", "SpadeQ.gif",
        // 大小王
        "JOKER-A.gif", "JOKER-B.gif"
    };

    qDebug() << "总共可用牌数:" << allCards.size() << "张";
    qDebug() << "红心牌:" << "Heart2-Heart10, Heart11-Heart16";

    // 发牌按钮点击事件
    QObject::connect(dealCardBtn, &QPushButton::clicked, [=]() {
        dealCardBtn->hide();
        smallBtnWidget->show();

        // 随机选择4张牌（允许重复）
        QVector<QString> selectedCards;
        for (int i = 0; i < 4; ++i) {
            int randomIndex = rand() % allCards.size();
            selectedCards.append(allCards[randomIndex]);
        }

        qDebug() << "=== 开始发牌 ===";
        qDebug() << "选中的牌:";
        for (int i = 0; i < selectedCards.size(); ++i) {
            qDebug() << "  牌" << (i+1) << ":" << selectedCards[i];
        }

        // 更新4张扑克牌的显示
        for (int i = 0; i < cardImageLabels.size(); ++i) {
            QString cardFile = selectedCards[i];

            // 尝试多个可能的路径
            QStringList possiblePaths = {
                "./assets/" + cardFile,      // 构建目录下的assets
                "assets/" + cardFile,        // 当前目录下的assets
                "../assets/" + cardFile      // 上一级的assets
            };

            QString imagePath;
            bool fileFound = false;

            for (const QString& path : possiblePaths) {
                if (QFile::exists(path)) {
                    imagePath = path;
                    fileFound = true;
                    break;
                }
            }

            if (!fileFound) {
                qDebug() << "文件不存在:" << cardFile;

                // 显示文件名（去掉.gif）
                QString displayName = cardFile;
                displayName.replace(".gif", "");
                cardImageLabels[i]->setText(displayName);
                cardImageLabels[i]->setStyleSheet(
                    "QLabel {"
                    "   font-size: 30px;"
                    "   font-weight: bold;"
                    "   color: #ff8800;"  // 橙色表示警告
                    "   background-color: transparent;"
                    "}");
                continue;
            }

            // 加载图片
            QPixmap pixmap(imagePath);

            if (!pixmap.isNull()) {
                // 清除文本，显示图片
                cardImageLabels[i]->setText("");
                cardImageLabels[i]->setPixmap(pixmap.scaled(
                    cardImageLabels[i]->size(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation
                    ));
                qDebug() << "成功加载:" << cardFile;
            } else {
                qDebug() << "加载失败:" << cardFile;

                // 显示文件名（去掉.gif）
                QString displayName = cardFile;
                displayName.replace(".gif", "");
                cardImageLabels[i]->setText(displayName);
                cardImageLabels[i]->setStyleSheet(
                    "QLabel {"
                    "   font-size: 30px;"
                    "   font-weight: bold;"
                    "   color: #ff4444;"  // 红色表示错误
                    "   background-color: transparent;"
                    "}");
            }
        }
        qDebug() << "=== 发牌完成 ===\n";
    });

    // 重置按钮点击事件
    QObject::connect(rightBtn3, &QPushButton::clicked, [=]() {
        smallBtnWidget->hide();
        dealCardBtn->show();

        qDebug() << "重置牌局";

        // 重置扑克牌显示
        for (int i = 0; i < cardImageLabels.size(); ++i) {
            cardImageLabels[i]->clear();
            cardImageLabels[i]->setText("?");
            cardImageLabels[i]->setStyleSheet(
                "QLabel {"
                "   font-size: 80px;"
                "   font-weight: bold;"
                "   color: #aaa;"
                "   background-color: transparent;"
                "}");
        }
    });

    rightOuterLayout->addWidget(dealCardBtn);
    rightOuterLayout->addWidget(smallBtnWidget);

    rightWidget->setMinimumWidth(150);
    bottomLayout->addWidget(rightWidget, 1);

    mainLayout->addWidget(bottomWidget, 1);

    w.show();
    return a.exec();
}

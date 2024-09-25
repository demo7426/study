#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class CForm;
}

class CForm : public QWidget
{
    Q_OBJECT

public:
    explicit CForm(QWidget *parent = nullptr);
    ~CForm();

private:
    QString m_strLoadFilePath = "";                     //用于保存加载的文件路径


    Ui::CForm *ui;

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

public:
    //判定是否已经加载文件
    //返回值:true--已加载;false--未加载
    inline bool IsLoadFile(void) const noexcept
    {
        return m_strLoadFilePath.isEmpty()? false: true;
    }

    //获取加载文件的路径
    inline QString GetLoadFilePath(void) const noexcept
    {
        return m_strLoadFilePath;
    }

    //加载文件到文本中显示
    void LoadFileToText(QString _FilePath);

    //拷贝Text
    void TextCopy(void);

    //粘贴Text
    void TextPaste(void);

    //剪切Text
    void TextCut(void);

    //设置Text的字体
    void SetTextFont(void);
};

#endif // FORM_H

#pragma once

const int PCX_HEADER_SIZE = 128;
const int PCX_HEADER_FLAG = 10;
const int PCX_HEADER_ENCODE = 1;
const int PCX_VER_SUPPORT = 5;

#pragma pack(1)
typedef struct         		// pcx�ļ�ͷ
{
    BYTE flag;				// ���
    BYTE version;			// �汾��
    BYTE encodeing;			// ���뷽ʽ
    BYTE bitsPrePixel;		// ƽ������λ��
    WORD xMin;				// ��СX
    WORD yMin;				// ��СY
    WORD xMax;				// ���X
    WORD yMax;				// ���Y
    WORD hRes;				// ˮƽ�ֱ���
    WORD vRes;				// ��ֱ�ֱ���
    BYTE palette[48];		// 16ɫ��ɫ��
    BYTE reserved;			// ����
    BYTE planes;			// ƽ����
    WORD bytesPreLine;		// ÿ���ֽ���
    WORD paletteType;		// ��ɫ�����͡�1����ɫ��ڰף�2���Ҷ�
    BYTE filler[58];
}PCX_HEADER, *PPCX_HEADER;
#pragma pack()

class CPcxFileHeader
{
public:
    CPcxFileHeader();
    ~CPcxFileHeader();

    bool ReadHeader(std::ifstream& file);
    bool WriteHeader(std::ofstream& file);
    int GetBytesPreLine() const { return m_data.bytesPreLine; }
    void SetBytesPreLine(int bytesPreLine) { m_data.bytesPreLine = bytesPreLine; }
    int GetBitsPrePixel() const { return m_data.bitsPrePixel; }
    void SetBitsPrePixel(int bitsPrePixel) { m_data.bitsPrePixel = bitsPrePixel; }
    int GetBmpWidth() const { return (m_data.xMax - m_data.xMin + 1); }
    void SetBmpWidth(int width);
    int GetBmpHeight() const { return (m_data.yMax - m_data.yMin + 1); }
    void SetBmpHeight(int height);
    int GetPlanes() const { return m_data.planes; }
    int GetVersion() const { return m_data.version; }

protected:
    PCX_HEADER m_data;
};


#pragma once
/* This header file was written based on these web pages.
1. http://d.hatena.ne.jp/buti2112/touch/20110305/1299354753
2. http://torokeru.tv/mameblog/?p=309
*/
template<class T>
class ISingleton {
	// [act]�V���O���g���N���X�̊��N���X
	T& operator=(const ISingleton<T>&);
	ISingleton(const ISingleton<T>&);
protected:
	ISingleton() {};
	virtual ~ISingleton() {};
public:
	static T& GetInstance() {
		static T ins;
		return ins;
	}
};
/* �g����:
	1.	���̃C���^�[�t�F�C�X���g�p����N���X�ŁAISingleton���p�u���b�N�p������B
		�������e���v���[�g�w��̓C���^�[�t�F�C�X���g�p����N���X�̖��O�Ƃ���B
	2.	���̃C���^�[�t�F�C�X���g�p����N���X�ɂ����āA�R���X�g���N�^�ƃf�X�g���N�^��
		�v���C�x�[�g�����o�Ƃ��Đ錾����B
	3.	���̃C���^�[�t�F�C�X���g�p����N���X�ɂ����āA
			friend ISingleton<ClassName>
		���L�q���A���̃N���X ISingleton ����C���^�[�t�F�C�X���g�p����N���X��
		private / protected �����o�ɃA�N�Z�X�ł���悤�ɂ���B
	4.	1-3�̑���ɂ���ăC���^�[�t�F�C�X���g�p����N���X�̃R���X�g���N�^��
		���� ISingleton �N���X����̂݌Ăׂ�悤�ɂȂ�A�O������͈�ؐ錾�ł��Ȃ��Ȃ�B

	5.	�Ăяo���͈ȉ��̃R�[�h�ōs���B����̂݃C���X�^���X�����͎����ōs����B
			ClassName& ValName = ClassName::GetInstance();
		�� �ȉ��̂悤�Ȓʏ�̃C���X�^���X�����̓R���p�C���G���[�ƂȂ�
			ClassName hoge;
	6.	�֐��Ăяo���͎��̃R�[�h�ōs��(�Q�ƌ^�Ȃ̂�.�A�N�Z�X)
			ValName.FunctionName(p1,p2,...);

������:
	// �錾�� //
	class CHoge : public ISingleton<CHoge>{	// ISingleton���p�u���b�N�p��		�g���� 1.
		friend ISingleton<Hoge>;			// ISingleton�N���X���t�����h�錾	�g���� 3.
	private:
		CHoge();							// �R���X�g���N�^��private�錾		�g���� 2.
		~CHoge();							// �@�f�X�g���N�^��private�錾		�g���� 2.
		int m_memberVariable;				// �ȉ��Ǝ��̃����o�ϐ��Ȃ�

	public:
		int Method1();						// �ȉ��Ǝ��̃��\�b�h�Ȃ�
	}

	// �Ăяo���� //
	CHoge& instance = CHoge::GetInstance();	// �C���X�^���X�̐������@			�g���� 5.
	int a = instance.Method1();				// �N���X���\�b�h�̎g�p				�g���� 6.
*/
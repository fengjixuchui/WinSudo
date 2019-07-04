#pragma once
#include <Windows.h>
#include "bstatus.h"
#include <ntsecapi.h>
#define BSAPI __stdcall

enum AUTH_TYPE {
	System,
	LocalService,
	AnonymousLogon,
	Other
};

typedef struct _USER_NAME_AND_ATTRIBUTESA {
	LPSTR UserName;
	DWORD Attributes;
	DWORD IsSid;
}USER_NAME_AND_ATTRIBUTESA, *PUSER_NAME_AND_ATTRIBUTESA;
typedef struct _GROUPS {
	DWORD dwUserNamesAndAttributesCount;
	USER_NAME_AND_ATTRIBUTESA NamesAndAttributes[ANYSIZE_ARRAY];
}GROUPS, *PGROUPS;

typedef struct _LOGON_SESSION_DATA {
	ULONG               Size;
	LUID                LogonId;
	LSA_UNICODE_STRING  UserName;
	LSA_UNICODE_STRING  LogonDomain;
	LSA_UNICODE_STRING  AuthenticationPackage;
	ULONG               LogonType;
	ULONG               Session;
	PSID                Sid;
	LARGE_INTEGER       LogonTime;

	LSA_UNICODE_STRING  LogonServer;
	LSA_UNICODE_STRING  DnsDomainName;
	LSA_UNICODE_STRING  Upn;

	ULONG UserFlags;

	LSA_LAST_INTER_LOGON_INFO LastLogonInfo;
	LSA_UNICODE_STRING LogonScript;
	LSA_UNICODE_STRING ProfilePath;
	LSA_UNICODE_STRING HomeDirectory;
	LSA_UNICODE_STRING HomeDirectoryDrive;

	LARGE_INTEGER LogoffTime;
	LARGE_INTEGER KickOffTime;
	LARGE_INTEGER PasswordLastSet;
	LARGE_INTEGER PasswordCanChange;
	LARGE_INTEGER PasswordMustChange;
}LOGON_SESSION_DATA, *PLOGON_SESSION_DATA;

//��Ȩ����, ����ʹ�û�������
typedef LONGLONG PRIVILEGE_VALUE, *PPRIVILEGE_VALUE;
#define SE_CREATE_TOKEN_VALUE							0x0000000000000001
#define SE_ASSIGNPRIMARYTOKEN_VALUE						0x0000000000000002
#define SE_LOCK_MEMORY_VALUE							0x0000000000000004
#define SE_INCREASE_QUOTA_VALUE							0x0000000000000008
#define SE_UNSOLICITED_INPUT_VALUE						0x0000000000000010
#define SE_MACHINE_ACCOUNT_VALUE						0x0000000000000020
#define SE_TCB_VALUE									0x0000000000000040
#define SE_SECURITY_VALUE								0x0000000000000080
#define SE_TAKE_OWNERSHIP_VALUE							0x0000000000000100
#define SE_LOAD_DRIVER_VALUE							0x0000000000000200
#define SE_SYSTEM_PROFILE_VALUE							0x0000000000000400
#define SE_SYSTEMTIME_VALUE								0x0000000000000800
#define SE_PROF_SINGLE_PROCESS_VALUE					0x0000000000001000
#define SE_INC_BASE_PRIORITY_VALUE						0x0000000000002000
#define SE_CREATE_PAGEFILE_VALUE						0x0000000000004000
#define SE_CREATE_PERMANENT_VALUE						0x0000000000008000
#define SE_BACKUP_VALUE									0x0000000000010000
#define SE_RESTORE_VALUE								0x0000000000020000
#define SE_SHUTDOWN_VALUE								0x0000000000040000
#define SE_DEBUG_VALUE									0x0000000000080000
#define SE_AUDIT_VALUE									0x0000000000100000
#define SE_SYSTEM_ENVIRONMENT_VALUE						0x0000000000200000
#define SE_CHANGE_NOTIFY_VALUE							0x0000000000400000
#define SE_REMOTE_SHUTDOWN_VALUE						0x0000000000800000
#define SE_UNDOCK_VALUE									0x0000000001000000
#define SE_SYNC_AGENT_VALUE								0x0000000002000000
#define SE_ENABLE_DELEGATION_VALUE						0x0000000004000000
#define SE_MANAGE_VOLUME_VALUE							0x0000000008000000
#define SE_IMPERSONATE_VALUE							0x0000000010000000
#define SE_CREATE_GLOBAL_VALUE							0x0000000020000000
#define SE_TRUSTED_CREDMAN_ACCESS_VALUE					0x0000000040000000
#define SE_RELABEL_VALUE								0x0000000080000000
#define SE_INC_WORKING_SET_VALUE						0x0000000100000000
#define SE_TIME_ZONE_VALUE								0x0000000200000000
#define SE_CREATE_SYMBOLIC_LINK_VALUE					0x0000000400000000
#define SE_DELEGATE_SESSION_USER_IMPERSONATE_VALUE		0x0000000800000000

#define SE_ALL_PRIVILEGE_VALUE							0x0000000FFFFFFFFF		//������Ȩ
#define SE_NO_PRIVILEGE_VALUE							0x0000000000000000		//����Ȩ

#define SE_DISABLE_PRIVILEGE_VALUE						0x1000000000000000		//����������Ȩ, ���ǿ�������



//SeCreateUserTokenEx dwFlags:

//��Ȩ��ʶ:(��ʾ���ָ������Ȩ, ��������, ��ѡ)
#define SE_CREATE_USE_PRIVILEGES_VALUE					0x00000001	//��ʾ TokenPrivileges ������ָ�� PRIVILEGE_VALUE ��ָ��
#define SE_CREATE_USE_TOKEN_PRIVILEGES					0x20000000	//��ʾ TokenPrivileges ������ָ�� TOKEN_PRIVILEGES ��ָ��
#define SE_CREATE_USE_PRIVILEGES	SE_CREATE_USE_PRIVILEGES_VALUE

//����ı�ʶ��ѡһ, ���򷵻� BSTATUS_INVALID_PARAMETER
#define SE_CREATE_USE_GROUPS							0x00000002	//��ʾ TokenGroup ���������� PGROUPS
#define SE_CREATE_USE_TOKEN_GROUPS						0x00000004	//��ʾ TokenGroup ���������� PTOKEN_GROUPS, �� SE_CREATE_USE_GROUPS ������

#define SE_CREATE_USE_DACL								0x00000008	//��ʾʹ�ÿ�ѡ���� TokenDefaultDacl, ���򽫺��� TokenDefaultDacl ����
#define SE_CREATE_USE_TOKEN_SOURCE						0x00000010	//��ʾʹ�ÿ�ѡ���� TokenSource, ���򽫺��� TokenSource ����

#define SE_CREATE_DISABLE_ALL_PRIVILEGES				0x10000000	//�� TokenPrivileges |= SE_DISABLE_PRIVILEGE_VALUE; ��ͬ

//Ĭ�ϵı�ʶ���
#define SE_CREATE_DEFAULT								SE_CREATE_USE_PRIVILEGES|SE_CREATE_USE_GROUPS


//��Ȩ����
#define PRIVILEGE_COUNT	36




//��ʼ��dll, �ڵ����κι���ǰ��Ҫ�ɹ�����һ��
BSTATUS BSAPI SeInitialDll();
//�ͷ�dll, ж��dllǰ����
BSTATUS BSAPI SeReleaseDll();

//����һ����������
BSTATUS BSAPI SeCreateUserTokenExA(
	PHANDLE			TokenHandle,						//���շ��ؾ����ָ��
	DWORD			dwFlags,							//��ʶ����
	TOKEN_TYPE		TokenType,							//���Ƶ�����
	AUTH_TYPE		AuthType,							//��֤ID����,ָ��Ϊ����ʱ��Ҫ�ṩ��һ������,���򽫺���
	LUID			AuthId					OPTIONAL,	//AuthType Ϊ Other ʱ��Ҫ�˲���
	LPCSTR			TokenUser,							//���Ƶ��û���
	LPVOID			TokenGroup,							//ָ��������dwFlags����
	LPVOID			TokenPrivileges,					//ָ��������dwFlags����
	LPCSTR			TokenOwner,							//�����������û���
	LPCSTR			TokenPrimaryGroup,					//�������û�����
	PTOKEN_SOURCE	TokenSource				OPTIONAL,	//������Դ
	PTOKEN_DEFAULT_DACL	TokenDefaultDacl	OPTIONAL,	//����Ĭ�����ɷ��ʿ����б�
	SECURITY_IMPERSONATION_LEVEL SecurityImpersonationLevel //��ȫģ�⼶��
);

BSTATUS BSAPI SeCreateUserTokenA(
	PHANDLE			TokenHandle,
	AUTH_TYPE		AuthType,
	LUID			AuthId,			OPTIONAL
	LPCSTR			TokenUser,
	PGROUPS			TokenGroup,
	PRIVILEGE_VALUE TokenPrivileges,
	LPCSTR			TokenPrimaryGroup
);

//�����ṩ�����ƴ���һ������������Ȩ�����Ƹ���
BSTATUS BSAPI SeEnablePrivilegesToken(IN OUT PHANDLE hToken, IN PRIVILEGE_VALUE EnablePrivileges);

//��ָ�����߳�����ָ���ķ�������
BSTATUS BSAPI SePrivilegeEscalationThread(DWORD dwThreadId, HANDLE hToken);

//��Ȩ������ TOKEN_PRIVILEGES �ṹ�Ļ���
BSTATUS BSAPI RtlTokenPrivilegesToPrivilegeValue(IN PTOKEN_PRIVILEGES tp, IN BOOL EnabledOnly, OUT PPRIVILEGE_VALUE privileges);
BSTATUS BSAPI RtlPrivilegeValueToTokenPrivileges(IN PRIVILEGE_VALUE privileges, OUT PTOKEN_PRIVILEGES tp, IN OUT PDWORD size);

//GROUPS �� TOKEN_GROUPS �ṹ������ת��
BSTATUS BSAPI RtlTokenGroupsToGroupsA(IN PTOKEN_GROUPS tg, OUT PGROUPS groups, IN OUT PDWORD size);
BSTATUS BSAPI RtlGroupsToTokenGroupsA(IN PGROUPS groups, OUT PTOKEN_GROUPS tg, IN OUT PDWORD size);

//��ָ���Ľ���/�߳�
BSTATUS BSAPI SeReferenceProcess(IN DWORD dwProcessId, OUT PHANDLE hProcess);
BSTATUS BSAPI SeReferenceThread(IN DWORD dwThreadId, OUT PHANDLE hThread);

//��ָ������/�̵߳ķ�������
BSTATUS BSAPI SeReferenceProcessPrimaryToken(IN DWORD dwProcessId, OUT PHANDLE hToken);
BSTATUS BSAPI SeReferenceThreadToken(IN DWORD dwThreadId, OUT PHANDLE hToken);

//��ȡ/����������Ϣ
DWORD BSAPI SeQueryInformationToken(HANDLE hToken, TOKEN_INFORMATION_CLASS info, LPVOID mem);
BSTATUS BSAPI SeSetInformationToken(HANDLE hToken, TOKEN_INFORMATION_CLASS info, LPVOID mem, DWORD memlen);

//��¼�ػ�ö��
BSTATUS BSAPI SeEnumLogonSessionsLuid(IN PDWORD count, OUT PLUID list, IN OUT PDWORD size);
BSTATUS BSAPI SeQueryLogonSessionInformation(IN PLUID luid, OUT PLOGON_SESSION_DATA *_data);
BSTATUS BSAPI SeFreeLogonSessionData(PLOGON_SESSION_DATA block);

//�û�����PSID����
PSID BSAPI SeReferenceUserNameA(LPCSTR user);
LPSTR BSAPI SeReferenceSidA(PSID sid);

//��ȡһ�����������Ƹ���
BSTATUS BSAPI SeReferenceEscalationToken(OUT PHANDLE hToken);
//�ر����Ƹ���
BSTATUS BSAPI SeDereferenceEscalationToken(IN HANDLE hToken);

//�ͷ�ʹ��API������ڴ�
BSTATUS BSAPI SeFreeAllocate(LPVOID _block);


BSTATUS BSAPI SeSingleGroupsAddNameA(
	IN LPCSTR MemberName,
	IN DWORD Attributes,
	IN PGROUPS Source,
	OUT PGROUPS Destination,
	IN OUT PDWORD BufferSize);

BSTATUS BSAPI SeSingleGroupsAddSid(
	IN PSID MemberSid,
	IN DWORD Attributes,
	IN PGROUPS Source,
	OUT PGROUPS Destination,
	IN OUT PDWORD BufferSize);

BSTATUS BSAPI SeSingleTokenGroupsAddNameA(
	IN LPCSTR MemberName,
	IN DWORD Attributes,
	IN PTOKEN_GROUPS Source,
	OUT PTOKEN_GROUPS Destination,
	IN OUT PDWORD BufferSize);

BSTATUS BSAPI SeSingleTokenGroupsAddSid(
	IN PSID MemberSid,
	IN DWORD Attributes,
	IN PTOKEN_GROUPS Source,
	OUT PTOKEN_GROUPS Destination,
	IN OUT PDWORD BufferSize);


BSTATUS BSAPI PsCreateUserProcessW(
	HANDLE hUserToken,
	LPCWSTR lpApplicationName,
	LPWSTR lpCommandLine,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCWSTR lpCurrentDirectory,
	LPSTARTUPINFOW lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation);

BSTATUS BSAPI PsCreateUserProcessA(
	HANDLE hUserToken,
	LPCSTR lpApplicationName,
	LPSTR lpCommandLine,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCSTR lpCurrentDirectory,
	LPSTARTUPINFOA lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation);

#define PsCreateProcessWithTokenA	PsCreateUserProcessA
#define PsCreateProcessWithTokenW	PsCreateUserProcessW
#define PsCreateProcessAsUserA		PsCreateProcessWithTokenA
#define PsCreateProcessAsUserW		PsCreateProcessWithTokenW

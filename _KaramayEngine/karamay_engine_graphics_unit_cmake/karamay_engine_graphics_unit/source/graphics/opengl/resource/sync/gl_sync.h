#ifndef GL_SYNC_H
#define GL_SYNC_H

#include "public/glew.h"

enum class gl_sync_result : GLenum
{
	ALREADY_SIGNALED = GL_ALREADY_SIGNALED,
	TIMEOUT_EXPIRED = GL_TIMEOUT_EXPIRED,
	CONDITION_SATISFIED = GL_CONDITION_SATISFIED,
	WAIT_FAILED = GL_WAIT_FAILED
};

class gl_fence
{
public:
	gl_fence()
	{
		_sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	}

	~gl_fence()
	{
		glClientWaitSync(_sync, GL_SYNC_FLUSH_COMMANDS_BIT, 0);
		glDeleteSync(_sync);
	}

public:

	// ����cpu��ǰ�̣߳��ȴ��ź�
	gl_sync_result client_wait(uint32 timeout)
	{
		// GL_SYNC_FLUSH_COMMANDS_BIT make sure sync obj has been in command queue
		// glFlush();
		return static_cast<gl_sync_result>(glClientWaitSync(_sync, GL_SYNC_FLUSH_COMMANDS_BIT, timeout));
	}

	// cpu�������أ�����gpu���У��޷�����GPU�������������µ�����ȴ��ź�
	void server_wait()
	{
		glFlush(); // make sure you have flush all commands to gpu(make sure sync obj has been in the command queue)
		// this func does not have GL_SYNC_FLUSH_COMMANDS_BIT bitfield ��������
		glWaitSync(_sync, 0, 0);
	}

	void query()
	{
		//glGetSynciv();
	}

	bool check()
	{
		return glIsSync(_sync);
	}

private:

	GLsync _sync;

};

#endif
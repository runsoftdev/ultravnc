#pragma once

class ClinetConnection;

class CMenuExecutor
{
public:
	CMenuExecutor(ClientConnection *_this);
	~CMenuExecutor();

private:
	ClientConnection *_this;


};


#ifndef RENDER_COMMAND_HPP
#define RENDER_COMMAND_HPP

class RenderCommand;
class RenderComponent;

class RenderCommand {
private:
	RenderComponent* mpRenderC;
	unsigned short mfEnables{ 0x00 };

public:

	enum {
		FRAMEBUFFER = 0x0001,
		SHADER = 0x0002,
		MESH = 0x0004,
		MODEL_MATRIX = 0x0008,
		VIEW_MATRIX = 0x0010,
		PROJECTION_MATRIX = 0x0020,
		CLEAR_COLOR = 0x0040,
		CLEAR_DEPTH = 0x0080,
		DEPTH_TEST = 0x0100
	};

	static bool UsesSameFramebuffer(const RenderCommand* pcLHS,
		const RenderCommand* pcRHS);
	static bool UsesSameShader(const RenderCommand* pcLHS,
		const RenderCommand* pcRHS);
	static bool UsesSameMesh(const RenderCommand* pcLHS,
		const RenderCommand* pcRHS);
	static bool UsesSameModelMatrix(const RenderCommand* pcLHS,
		const RenderCommand* pcRHS);
	static bool UsesSameViewMatrix(const RenderCommand* pcLHS,
		const RenderCommand* pcRHS);
	static bool UsesSameProjectionMatrix(const RenderCommand* pcLHS,
		const RenderCommand* pcRHS);
	RenderCommand(RenderComponent* pRenderC);

	void Enable(unsigned short fEnables);
	void Execute();
};

// idea to allow new arbitrary render commands to be defined

#endif
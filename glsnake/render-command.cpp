#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera-component.hpp"
#include "framebuffer.hpp"
#include "mesh.hpp"
#include "projection.hpp"
#include "render-command.hpp"
#include "render-component.hpp"
#include "render-engine.hpp"
#include "shader.hpp"
#include "transform-component.hpp"

RenderCommand::RenderCommand(RenderComponent* pRenderC) : mpRenderC{ pRenderC } {
	mfEnables |= FRAMEBUFFER;
	mfEnables |= SHADER;
	mfEnables |= MESH;
	mfEnables |= MODEL_MATRIX;
	mfEnables |= VIEW_MATRIX;
	mfEnables |= PROJECTION_MATRIX;
}

void RenderCommand::Execute() {
	//if (mfEnables & FRAMEBUFFER) {
	//	mpRenderC->GetFramebuffer()->Enable();
	//}

	if (mfEnables & SHADER) {
		mpRenderC->GetMaterial()->Enable();
	}

	if (mfEnables & MESH) {
		mpRenderC->GetMesh()->Enable();
	}

	// set individual matrices

	if (mfEnables & MODEL_MATRIX) {
		TransformComponent* pTransformC = mpRenderC->GetComponent<TransformComponent>();
		RenderEngine::Instance().mMMatrix = pTransformC->ModelMatrix();
	}

	if (mfEnables & VIEW_MATRIX) {
		CameraComponent* pCameraC = mpRenderC->GetCamera();
		RenderEngine::Instance().mVMatrix = pCameraC->ViewMatrix();
	}

	// set individual matrices & cache

	if (mfEnables & PROJECTION_MATRIX) {
		Projection* pProjection = mpRenderC->GetProjection();
		RenderEngine::Instance().mPMatrix = pProjection->ProjectionMatrix();
		RenderEngine::Instance().mVPMatrix = RenderEngine::Instance().mPMatrix *
			RenderEngine::Instance().mVMatrix; 
		RenderEngine::Instance().mMVPMatrix = RenderEngine::Instance().mVPMatrix * RenderEngine::Instance().mMMatrix;

		mpRenderC->GetMaterial()->SetUniform(Uniform::MVP_MATRIX,
			RenderEngine::Instance().mMVPMatrix);
	}

	// cache

	else if (mfEnables & VIEW_MATRIX) {
		RenderEngine::Instance().mVPMatrix = RenderEngine::Instance().mPMatrix *
			RenderEngine::Instance().mVMatrix;
		RenderEngine::Instance().mMVPMatrix = RenderEngine::Instance().mVPMatrix * RenderEngine::Instance().mMMatrix;

		mpRenderC->GetMaterial()->SetUniform(Uniform::MVP_MATRIX,
			RenderEngine::Instance().mMVPMatrix);
	}

	else if ((mfEnables & MODEL_MATRIX) && (mfEnables & ~VIEW_MATRIX) &&
		(mfEnables & ~PROJECTION_MATRIX)) {
		RenderEngine::Instance().mMVPMatrix = RenderEngine::Instance().mVPMatrix *
			RenderEngine::Instance().mMMatrix;

		mpRenderC->GetMaterial()->SetUniform(Uniform::MVP_MATRIX,
			RenderEngine::Instance().mMVPMatrix);
	}

	if (mfEnables & CLEAR_COLOR) {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	if (mfEnables & CLEAR_DEPTH) {
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	if (mfEnables & DEPTH_TEST) {
		glEnable(GL_DEPTH_TEST);
	}

	mpRenderC->GetMaterial()->UploadUniforms();

	glDrawArrays(mpRenderC->GetRenderMode(), 0, 
		mpRenderC->GetNumVertices());
}

// static 
bool RenderCommand::UsesSameFramebuffer(const RenderCommand* pcLHS, const RenderCommand*
	pcRHS) {
	return (*pcLHS->mpRenderC->GetFramebuffer()) == (*pcRHS->mpRenderC->GetFramebuffer());
}

bool RenderCommand::UsesSameShader(const RenderCommand* pcLHS, const RenderCommand*
	pcRHS) {
	return (*pcLHS->mpRenderC->GetShader()) == (*pcRHS->mpRenderC->GetShader());
}

bool RenderCommand::UsesSameMesh(const RenderCommand* pcLHS, const RenderCommand*
	pcRHS) {
	return (*pcLHS->mpRenderC->GetMesh()) == (*pcRHS->mpRenderC->GetMesh());
}

bool RenderCommand::UsesSameModelMatrix(const RenderCommand* pcLHS, const RenderCommand*
	pcRHS) {
	return pcLHS->mpRenderC->GetComponent<TransformComponent>() == pcRHS->mpRenderC->
		GetComponent<TransformComponent>();
}

bool RenderCommand::UsesSameViewMatrix(const RenderCommand* pcLHS, const RenderCommand*
	pcRHS) {
	return pcLHS->mpRenderC->GetCamera() == pcRHS->mpRenderC->GetCamera();
}

// should perhaps change to a deeper comparison,
// perhaps upon converting to a different 
// intermediate representation

bool RenderCommand::UsesSameProjectionMatrix(const RenderCommand* pcLHS, const RenderCommand*
	pcRHS) {
	return pcLHS->mpRenderC->GetProjection() == pcRHS->mpRenderC->GetProjection();
}

void RenderCommand::Enable(unsigned short fEnables) {
	mfEnables |= fEnables;
}

// might consider changing things around so that 
// intermediate data representations are passed around 
// rather than components
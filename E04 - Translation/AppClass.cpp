#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Zach Winnewisser - zmw7710@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Make MyMesh object
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(2.0f, C_BROWN);

	//Make MyMesh object
	m_pMesh1 = new MyMesh();
	m_pMesh1->GenerateCube(1.0f, C_WHITE);

	//first row of antenna
	pos.push_back(glm::vec3(-6, 6, 0));
	pos.push_back(glm::vec3(6, 6, 0));
	//end of first row with antenna

	//2nd row of antenna
	pos.push_back(glm::vec3(-4, 4, 0));
	pos.push_back(glm::vec3(4, 4, 0));
	//end of 2nd row with antenna

	//row above eyes
	pos.push_back(glm::vec3(0, 2, 0));
	pos.push_back(glm::vec3(-2, 2, 0));
	pos.push_back(glm::vec3(-4, 2, 0));
	pos.push_back(glm::vec3(-6, 2, 0));
	pos.push_back(glm::vec3(2, 2, 0));
	pos.push_back(glm::vec3(4, 2, 0));
	pos.push_back(glm::vec3(6, 2, 0));
	//end of row above eyes

	//row with eyes
	pos.push_back(glm::vec3(0, 0, 0));
	pos.push_back(glm::vec3(-2, 0, 0));
	pos.push_back(glm::vec3(-6, 0, 0));
	pos.push_back(glm::vec3(-8, 0, 0));
	pos.push_back(glm::vec3(2, 0, 0));
	pos.push_back(glm::vec3(6, 0, 0));
	pos.push_back(glm::vec3(8, 0, 0));
	//end of row with eyes

	//row under eyes
	pos.push_back(glm::vec3(0, -2, 0));
	pos.push_back(glm::vec3(-2, -2, 0));
	pos.push_back(glm::vec3(-4, -2, 0));
	pos.push_back(glm::vec3(-6, -2, 0));
	pos.push_back(glm::vec3(-8, -2, 0));
	pos.push_back(glm::vec3(-10, -2, 0));
	pos.push_back(glm::vec3(2, -2, 0));
	pos.push_back(glm::vec3(4, -2, 0));
	pos.push_back(glm::vec3(6, -2, 0));
	pos.push_back(glm::vec3(8, -2, 0));
	pos.push_back(glm::vec3(10, -2, 0));
	//end of row under eyes

	//2nd row below eyes
	pos.push_back(glm::vec3(0, -4, 0));
	pos.push_back(glm::vec3(-2, -4, 0));
	pos.push_back(glm::vec3(-4, -4, 0));
	pos.push_back(glm::vec3(-6, -4, 0));
	pos.push_back(glm::vec3(-10, -4, 0));
	pos.push_back(glm::vec3(2, -4, 0));
	pos.push_back(glm::vec3(4, -4, 0));
	pos.push_back(glm::vec3(6, -4, 0));
	pos.push_back(glm::vec3(10, -4, 0));
	//end of 2nd row below eyes

	//2nd to last row
	pos.push_back(glm::vec3(-6, -6, 0));
	pos.push_back(glm::vec3(-10, -6, 0));
	pos.push_back(glm::vec3(6, -6, 0));
	pos.push_back(glm::vec3(10, -6, 0));
	//end of 2nd to last row 

	//last row
	pos.push_back(glm::vec3(-2, -8, 0));
	pos.push_back(glm::vec3(-4, -8, 0));
	pos.push_back(glm::vec3(2, -8, 0));
	pos.push_back(glm::vec3(4, -8, 0));
	//end of last row

}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//m_m4Object1 = m_m4Object1 * glm::rotate(matrix4(),.1f,AXIS_X);
	//m_m4Object1 = m_m4Object1 * glm::translate(matrix4(),glm::vec3(0,0,0.1f));


	//m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), ToMatrix4(m_qArcBall));
	//m_pMesh->Render(m4Projection, m4View, m_m4Object1);

	matrix4 moved;

	//loop through the position vector, then render and translate
	for (uint i = 0; i < pos.size();i++)
	{
		//scale them
		moved = glm::scale(matrix4(), glm::vec3(0.5, 0.5, 1));

		//go through pos and translate them into the specified location at i
		moved = glm::translate(moved,pos[i]);

		//render them
		m_pMesh->Render(m4Projection, m4View, moved);
		
		//actually translate them
		pos[i] = pos[i] + glm::vec3(0.1f, 0, 0);

	}
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	SafeDelete(m_pMesh1);
	//release GUI
	ShutdownGUI();
}
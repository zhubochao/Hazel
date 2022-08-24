#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel
{

	class HazelnutApp : public Application
	{
	public:
		HazelnutApp(ApplicationCommandLineArgs args)
			: Application("Hazel Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		~HazelnutApp()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new HazelnutApp(args);
	}

}
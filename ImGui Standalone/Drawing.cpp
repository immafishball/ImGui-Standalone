#include "Drawing.h"

LPCSTR Drawing::lpWindowName = "ImGui Standalone";
ImVec2 Drawing::vWindowSize = { 350, 75 };
ImGuiWindowFlags Drawing::WindowFlags = 0;
bool Drawing::bDraw = true;

void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw == true;
}

void Drawing::Draw()
{
	if (isActive())
	{
		ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
		{

			ImGui::Text("Create your own menu.");

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
		ImGui::End();

		/**
		* ImGui Notify Demo Start
		*/

		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGuiCond_Once);
		ImGui::SetNextWindowSize({ 550, 550 }, ImGuiCond_Once);
		ImGui::Begin("ImGui Notify Test Window");

		if (ImGui::CollapsingHeader("Examples without title", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::Button("Success"))
			{
				ImGui::InsertNotification({ ImGuiToastType::Success, 3000, "That is a success! %s", "(Format here)" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Warning"))
			{
				ImGui::InsertNotification({ ImGuiToastType::Warning, 3000, "This is a warning!" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Error"))
			{
				ImGui::InsertNotification({ ImGuiToastType::Error, 3000, "Segmentation fault" });
			}

			ImGui::SameLine();
			if (ImGui::Button("Info"))
			{
				ImGui::InsertNotification({ ImGuiToastType::Info, 3000, "Info about ImGui..." });
			}

			ImGui::SameLine();
			if (ImGui::Button("Info long"))
			{
				ImGui::InsertNotification({ ImGuiToastType::Info, 3000, "Hi, I'm a long notification. I'm here to show you that you can write a lot of text in me. I'm also here to show you that I can wrap text, so you don't have to worry about that." });
			}

			ImGui::SameLine();
			if (ImGui::Button("Notify with button"))
			{
				ImGui::InsertNotification({ ImGuiToastType::Error, 3000, "Click me!", []() {ImGui::InsertNotification({ImGuiToastType::Success, 3000, "Thanks for clicking!"});}, "Notification content" });
			}
		}

		if (ImGui::CollapsingHeader("Do it yourself", ImGuiTreeNodeFlags_DefaultOpen))
		{
			static char title[4096] = "Hello there!";
			ImGui::InputTextMultiline("Title", title, sizeof(title));

			static char content[4096] = "General Kenobi! \n- Grevious";
			ImGui::InputTextMultiline("Content", content, sizeof(content));

			static int duration = 5000; // 5 seconds
			ImGui::InputInt("Duration (ms)", &duration, 100);
			if (duration < 0) duration = 0; // Shouldn't be negative

			static const char* type_str[] = { "None", "Success", "Warning", "Error", "Info" };
			static ImGuiToastType type = ImGuiToastType::Success;
			IM_ASSERT(type < ImGuiToastType::COUNT);

			if (ImGui::BeginCombo("Type", type_str[(uint8_t)type]))
			{
				for (auto n = 0; n < IM_ARRAYSIZE(type_str); n++)
				{
					const bool isSelected = ((uint8_t)type == n);

					if (ImGui::Selectable(type_str[n], isSelected))
					{
						type = (ImGuiToastType)n;
					}

					if (isSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			static bool enable_title = true, enable_content = true;
			ImGui::Checkbox("Enable title", &enable_title);
			ImGui::SameLine();
			ImGui::Checkbox("Enable content", &enable_content);

			if (ImGui::Button("Show"))
			{
				ImGuiToast toast(type, duration);

				if (enable_title)
					toast.setTitle(title);

				if (enable_content)
					toast.setContent(content);

				ImGui::InsertNotification(toast);
			}
		}

		ImGui::End();

		/**
		 * ImGui Notify Demo End
		*/









		// YOUR CODE GOES HERE











		/**
		 * Notifications Rendering Start
		*/

		// Notifications style setup
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f); // Disable round borders
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f); // Disable borders

		// Notifications color setup
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.10f, 0.10f, 0.10f, 1.00f)); // Background color


		// Main rendering function
		ImGui::RenderNotifications();


		//——————————————————————————————— WARNING ———————————————————————————————
		// Argument MUST match the amount of ImGui::PushStyleVar() calls 
		ImGui::PopStyleVar(2);
		// Argument MUST match the amount of ImGui::PushStyleColor() calls 
		ImGui::PopStyleColor(1);

		/**
		 * Notifications Rendering End
		*/
	}

#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
#endif
}
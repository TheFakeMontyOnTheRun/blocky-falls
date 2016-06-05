#ifndef BF_CTITLESCREENVIEW
#define BF_CTITLESCREENVIEW
namespace BlockyFalls {
	class CTitleScreenView : public Vipper::IView, public Vipper::IRenderer::IClickListener {
		CPlayButton mButton;
		public:
		explicit CTitleScreenView(std::shared_ptr<Vipper::IRenderer> renderer);
		
		void show() override;
		void onClick( std::pair<int, int> position ) override;
	};
}
#endif
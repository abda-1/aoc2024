import dash
from dash import html, dcc
import dash_bootstrap_components as dbc


class Dashboard:
    def __init__(self, data_source=None):
        self.data_source = data_source
        self.app = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP])
        # Load all styles into a dictionary of callable functions
        self.styles = self.get_styles()
        
        # Set the app layout using the style functions
        self.app.layout = self.create_layout()
        
    def get_styles(self):
        # Return a dictionary where keys are style identifiers and values are functions
        # that return style dictionaries when called.
        
        return {
            "page": self.page_style,
            "card": self.card_style,
            "header": self.header_style,
            "subtitle": self.subtitle_style
        }

    def page_style(self):
        # This returns a style dict for the overall page
        return {
            "display": "flex",
            "flexDirection": "row",
            "height": "100vh",
            "width": "100vw",
            "margin": "0",
            "overflow": "hidden",
            "fontFamily": "-apple-system, BlinkMacSystemFont, 'SF Pro Display', 'SF Pro Text', 'Helvetica Neue', 'Lucida Grande', sans-serif",
            "background": "linear-gradient(to top right, #020617, #0f172a, #172554)"
        }

    def card_style(self):
        return {
            "backgroundColor": "rgba(255,255,255,0.05)",
            "backdropFilter": "blur(10px)",
            "-webkit-backdrop-filter": "blur(10px)",
            "borderRadius": "10px",
            "padding": "20px",
            "margin": "10px",
            "boxShadow": "0 4px 30px rgba(0,0,0,0.1)",
            "border": "1px solid rgba(255,255,255,0.3)",
            "display": "flex",
            "flexDirection": "column",
            "justifyContent": "center",
            "alignItems": "center"
        }


    def header_style(self):
        # Style for a main header text
        return {
            "fontSize": "24px",
            "fontWeight": "600",
            "color": "#ffffff",
            "textAlign": "center",
            "marginBottom": "10px"
        }

    def subtitle_style(self):
        # Style for a subtitle or secondary header text
        return {
            "fontSize": "18px",
            "fontWeight": "400",
            "color": "#e0e0e0",
            "textAlign": "center",
            "marginBottom": "10px"
        }

    def create_layout(self):
        # Use the style functions by calling them from self.styles dictionary
        return html.Div(
            style=self.styles["page"](),
            children=[
                # Left Card
                html.Div(
                    style=self.styles["card"](),
                    children=[
                        html.H1("Two", style=self.styles["header"]()),
                        html.H3("One", style=self.styles["subtitle"]()),
                    ]
                ),

                # Right Card
                html.Div(
                    style=self.styles["card"](),
                    children=[
                        html.H1("Telemetry Data", style=self.styles["header"]()),
                    ]
                )
            ]
        )

if __name__ == "__main__":
    dashboard = Dashboard()
    dashboard.app.run(debug=True)

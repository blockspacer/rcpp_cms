#include "utils.h"

void Utils::newline_to_br(std::string *str) {
	str_replace(str, "\r\n", "<br>");
	str_replace(str, "\n", "<br>");
}

void Utils::bbcode_evaluate_simple(std::string *str) {
	bbcpp::BBDocumentPtr doc = bbcode((*str));

	bbcpp::BBNodeList n = doc->getChildren();

	str->clear();

	for (uint32_t i = 0; i < n.size(); ++i) {
		eval_node(str, n[i]);
	}
}

bbcpp::BBDocumentPtr Utils::bbcode(const std::string &str) {
	bbcpp::BBDocumentPtr doc = bbcpp::BBDocument::create();

	doc->load(str);

	return doc;
}

void Utils::str_replace(std::string *str, const std::string &from, const std::string &to) {
	if (from.empty())
		return;

	size_t start_pos = 0;
	while ((start_pos = str->find(from, start_pos)) != std::string::npos) {
		str->replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

void Utils::eval_node(std::string *str, bbcpp::BBNodePtr node) {
	switch (node->getNodeType()) {
		case bbcpp::BBNode::NodeType::TEXT: {
			bbcpp::BBTextPtr t = node->downCast<bbcpp::BBTextPtr>();

			(*str) += t->getText();
			break;
		}
		case bbcpp::BBNode::NodeType::ELEMENT: {
			bbcpp::BBElementPtr e = node->downCast<bbcpp::BBElementPtr>();

            eval_element(str, e);

			break;
		}
		case bbcpp::BBNode::NodeType::ATTRIBUTE:
			break;
		case bbcpp::BBNode::NodeType::DOCUMENT:
			break;
	}

	bbcpp::BBNodeList n = node->getChildren();

	for (uint32_t i = 0; i < n.size(); ++i) {
		eval_node(str, n[i]);
	}
}

void Utils::eval_element(std::string *str, bbcpp::BBElementPtr element) {
	switch (element->getElementType()) {
		case bbcpp::BBElement::ElementType::SIMPLE: {

            if (element->getNodeName() == "b") {
                (*str) += "<span style=\"font-weight: bold;\">";
                return;
            }

            if (element->getNodeName() == "i") {
                (*str) += "<span style=\"font-style: italic;\">";
                return;
            }

            if (element->getNodeName() == "u") {
                (*str) += "<span style=\"text-decoration: underline;\">";
                return;
            }

            if (element->getNodeName() == "s") {
                (*str) += "<span style=\"text-decoration: line-through;\">";
                return;
            }


			break;
		}
		case bbcpp::BBElement::ElementType::VALUE: {
            //NYI
			break;
		}
		case bbcpp::BBElement::ElementType::PARAMETER: {
			break;
        }
		case bbcpp::BBElement::ElementType::CLOSING: {
            if (element->getNodeName() == "b") {
                (*str) += "</span>";
                return;
            }

            if (element->getNodeName() == "i") {
                (*str) += "</span>";
                return;
            }

            if (element->getNodeName() == "u") {
                (*str) += "</span>";
                return;
            }

            if (element->getNodeName() == "s") {
                (*str) += "</span>";
                return;
            }



			break;
        }
	}
}
#include <gtest/gtest.h>
#include "StringUtils.h" 
#include <RmlUi/Core/Input.h>

TEST(StringUtilsTest, ReplacesAllOccurrences)
{
    std::string original = "uno dos uno tres uno";
    const std::string from = "uno";
    const std::string to = "cuatro";
    std::string expected = "cuatro dos cuatro tres cuatro";
    //Remember original will change
    StringUtils::replaceAll(original, from, to);

    EXPECT_EQ(original, expected);
}

TEST(StringUtilsTest, HandlesOverlappingAndEmptyCases)
{

    std::string original = "ababab";
    std::string expected_overlap = "axabab"; 

    StringUtils::replaceAll(original, "aba", "axa");
    EXPECT_EQ(original, expected_overlap);
    
    std::string original_empty_to = "a-b-c";
    std::string expected_empty_to = "abc";


    StringUtils::replaceAll(original_empty_to, "-", "");
    EXPECT_EQ(original_empty_to, expected_empty_to);
}

TEST(StringUtilsTest, EscapesAllSpecialCharacters)
{
    const std::string original = "<h1>\"Hello & World\"</h1>";
    const std::string expected = "&lt;h1&gt;&quot;Hello &amp; World&quot;&lt;/h1&gt;";

    std::string result = StringUtils::escapeHtml(original);

    EXPECT_EQ(result, expected);
}

TEST(StringUtilsTest, HandlesAmpersandCorrectlyFirst)
{
    const std::string original = "Este texto ya tiene un &amp; y un <.";
    const std::string expected = "Este texto ya tiene un &amp;amp; y un &lt;.";

    std::string result = StringUtils::escapeHtml(original);

    EXPECT_EQ(result, expected);
}

TEST(StringUtilsTest, EscapesCurlyBracesForRmlUiDataBinding)
{
    const std::string original = "JSON: {\"id\": 100, \"data\": \"<value>\"}}";
    const std::string expected = "JSON: &#123;&quot;id&quot;: 100, &quot;data&quot;: &quot;&lt;value&gt;&quot;&#125;&#125;";
    std::string result = StringUtils::escapeHtml(original);

    EXPECT_EQ(result, expected);
}

TEST(StringUtilsTest, HandlesSequences) {
    EXPECT_EQ(StringUtils::getDelimiter("t"), 't');
    EXPECT_EQ(StringUtils::getDelimiter("ta"), 't');
    EXPECT_EQ(StringUtils::getDelimiter("\\t"), '\t');
    EXPECT_EQ(StringUtils::getDelimiter("\\n"), '\n');
    EXPECT_EQ(StringUtils::getDelimiter("\\r"), '\r');
    EXPECT_EQ(StringUtils::getDelimiter("\\\\"), '\\');
}


TEST(StringUtilsTest, EnumToString) {
    EXPECT_EQ(StringUtils::getStringFronEnum(Rml::Input::KI_A), "KI_A");
}

TEST(StringUtilsTest, StringToEnum) {
    EXPECT_EQ(StringUtils::getEnumFronString("KI_SPACE"), Rml::Input::KI_SPACE);
    EXPECT_EQ(StringUtils::getEnumFronString(""), Rml::Input::KI_UNKNOWN);
}
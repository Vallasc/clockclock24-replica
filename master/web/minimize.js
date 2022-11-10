import { minify } from 'html-minifier';
import fs from 'fs';

try {
    console.log('Minimizing ./index.html');
    const data = fs.readFileSync('./index.html', 'utf8');
    let result = minify(data, {
        removeAttributeQuotes: true,
        collapseWhitespace: true,
        removeComments: true,
        removeRedundantAttributes: true,
        removeScriptTypeAttributes: true,
        removeStyleLinkTypeAttributes: true,
        removeTagWhitespace: true,
        useShortDoctype: true,
        minifyCSS: true,
        minifyJS: true
    });
    //fs.writeFileSync('./index.min.html', result);

    const page_h = 
`#ifndef WEB_PAGE_H
#define WEB_PAGE_H
#define WEB_PAGE "${result.replaceAll(`"`, `\\"`)}"
#endif`

    fs.writeFileSync('../include/web_page.h', page_h);
    console.log('Generated ../include/web_page.h');
} catch (err) {
    console.error(err);
}

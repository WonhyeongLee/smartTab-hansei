const path = require('path');
const webpack = require("webpack");
const nodeExternals = require('webpack-node-externals');
const HtmlWebPackPlugin = require('html-webpack-plugin');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');

const moduleObj = {
    rules: [
        {
            test: /\.(js|jsx|css)$/,
            exclude: /node_modules/,
            loader : 'babel-loader',
            options: {
                presets: ['@babel/env', '@babel/preset-react'],
                plugins: [
                  "@babel/plugin-proposal-class-properties"
                  ]
              }
        },
        {
          test: /\.css$/,
          use: [MiniCssExtractPlugin.loader, 'css-loader'],
        },
        {
          test: /\.svg$/,
          use:'@svgr/webpack',
        },
        {
          test: /\.(jpg|png|gif|svg)$/,
          loader:'file-loader',
          options: {
            name: '[name].[ext]',
          }
        },
        // {
        //   test:/\.svg$/,
        //   loader:'url-loader',
        //   options: {
        //     publicPath: './dist/',
        //     name: '[name].[ext]?[hash]',
        //     limit: 10000,
        //   }
        // },
    ],
};
module.exports = {
    devServer: {
      contentBase: path.join(__dirname, "/dist/"),
      host: "localhost",
      inline: true,
      port: 5000,
    },
  };

const client = {
  
  entry: {
    'client': './src/client/index.js'
  },
  target: 'web',
  mode: "development",
  module: moduleObj,
  resolve: {
    extensions: ['*','.js','.jsx','css']
},
  output: {
    filename: '[name].js',
    path: path.resolve(__dirname, 'dist/'),
    publicPath: "/dist/"
  },
  plugins: [
    new HtmlWebPackPlugin({
      template: 'src/client/index.html'
    }),
    new MiniCssExtractPlugin({ filename: 'app.css' })
  ]
}
const server = {
    entry: {
        'server': './src/server/server.js'
    },
    target: 'node',
    mode: "development",
    module: moduleObj,
    output: {
        filename: '[name].js',
        path: path.resolve(__dirname, 'dist')
    },
    externals: [nodeExternals()]
}
module.exports = [client];
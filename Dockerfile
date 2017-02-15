# Get latest Node version
FROM node:latest

# Create app directory
RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app

# Copy app source
COPY ./Web /usr/src/app 

# Install app dependencies & run Gulp tasks

RUN \
    npm install bower -g && \
    npm install gulp -g && \
	npm install && \
	bower install --allow-root && \
	gulp


# Expose port 
EXPOSE 3000

# Default run command
CMD [ "npm", "start" ]